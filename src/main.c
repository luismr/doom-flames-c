#include "fire.h"

void print_usage(const char *program_name) {
    printf("DOOM Fire Effect - Terminal Animation\n\n");
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -w, --width WIDTH     Set fire width (default: terminal width)\n");
    printf("  -h, --height HEIGHT   Set fire height (default: terminal height)\n");
    printf("  -f, --fps FPS         Set frames per second (default: 30)\n");
    printf("  -d, --wind DIR        Set wind direction (-1=left, 0=none, 1=right)\n");
    printf("  -o, --optimized       Use optimized rendering with Unicode blocks\n");
    printf("  -i, --intensity MODE  Fire intensity (0=red/orange, 1=classic, 2=hot white)\n");
    printf("  --help                Show this help message\n\n");
    printf("Controls:\n");
    printf("  q, ESC, Ctrl+C        Quit\n");
    printf("  SPACE                 Toggle pause\n");
    printf("  LEFT/RIGHT arrows     Change wind direction\n");
    printf("  +/-                   Increase/decrease speed\n\n");
    printf("Note: For best results, use a terminal with 256-color support.\n");
}

int parse_arguments(int argc, char *argv[], int *width, int *height, int *fps, int *wind, int *optimized, int *intensity) {
    *width = 0;   // 0 means auto-detect
    *height = 0;  // 0 means auto-detect
    *fps = 30;
    *wind = 0;
    *optimized = 0;
    *intensity = 0;  // 0 = red/orange focused (current)
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            return 0;  // Show help
        } else if ((strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) && i + 1 < argc) {
            *width = atoi(argv[++i]);
            if (*width <= 0 || *width > 200) {
                fprintf(stderr, "Error: Width must be between 1 and 200\n");
                return -1;
            }
        } else if ((strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) && i + 1 < argc) {
            *height = atoi(argv[++i]);
            if (*height <= 0 || *height > 100) {
                fprintf(stderr, "Error: Height must be between 1 and 100\n");
                return -1;
            }
        } else if ((strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fps") == 0) && i + 1 < argc) {
            *fps = atoi(argv[++i]);
            if (*fps <= 0 || *fps > 120) {
                fprintf(stderr, "Error: FPS must be between 1 and 120\n");
                return -1;
            }
        } else if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--wind") == 0) && i + 1 < argc) {
            *wind = atoi(argv[++i]);
            if (*wind < -1 || *wind > 1) {
                fprintf(stderr, "Error: Wind direction must be -1, 0, or 1\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--optimized") == 0) {
            *optimized = 1;
        } else if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--intensity") == 0) && i + 1 < argc) {
            *intensity = atoi(argv[++i]);
            if (*intensity < 0 || *intensity > 2) {
                fprintf(stderr, "Error: Intensity must be 0, 1, or 2\n");
                return -1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return -1;
        }
    }
    
    return 1;  // Success
}

void handle_input(Fire *fire, int *paused, int *fps, int *frame_delay) {
    if (!kbhit()) return;
    
    int ch = getch_nonblocking();
    if (ch == -1) return;
    
    switch (ch) {
        case 'q':
        case 'Q':
        case 27:  // ESC key
            running = 0;
            break;
            
        case ' ':  // Space - toggle pause
            *paused = !(*paused);
            break;
            
        case 'a':  // Left arrow or 'a' - wind left
        case 75:   // Left arrow (some terminals)
            fire->wind_direction = -1;
            break;
            
        case 'd':  // Right arrow or 'd' - wind right
        case 77:   // Right arrow (some terminals)
            fire->wind_direction = 1;
            break;
            
        case 's':  // 's' - no wind
            fire->wind_direction = 0;
            break;
            
        case '+':
        case '=':  // Increase speed
            if (*fps < 120) {
                (*fps)++;
                *frame_delay = 1000 / *fps;
            }
            break;
            
        case '-':
        case '_':  // Decrease speed
            if (*fps > 1) {
                (*fps)--;
                *frame_delay = 1000 / *fps;
            }
            break;
    }
}

int main(int argc, char *argv[]) {
    int width, height, fps, wind_direction, use_optimized, fire_intensity;
    
    // Parse command line arguments
    int parse_result = parse_arguments(argc, argv, &width, &height, &fps, &wind_direction, &use_optimized, &fire_intensity);
    if (parse_result == 0) {
        print_usage(argv[0]);
        return 0;
    } else if (parse_result == -1) {
        return 1;
    }
    
    // Initialize terminal
    if (!terminal_init()) {
        fprintf(stderr, "Error: Failed to initialize terminal\n");
        return 1;
    }
    
    // Setup signal handlers for graceful exit
    setup_signal_handlers();
    
    // Get terminal size if not specified
    if (width == 0 || height == 0) {
        int term_width, term_height;
        terminal_get_size(&term_width, &term_height);
        if (width == 0) width = term_width;
        if (height == 0) height = term_height - 1;  // Leave room to prevent scrolling
    }
    
    // Adjust height for optimized rendering (uses half-blocks)
    if (use_optimized) {
        height *= 2;  // Double the internal height for half-block rendering
    }
    
    // Create fire effect
    Fire *fire = fire_create(width, height, fire_intensity);
    if (!fire) {
        fprintf(stderr, "Error: Failed to create fire effect\n");
        terminal_cleanup();
        return 1;
    }
    
    // Set global fire for signal handler
    global_fire = fire;
    fire->wind_direction = wind_direction;
    
    // Initialize fire source
    fire_init_source(fire);
    
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Clear screen and hide cursor
    terminal_clear_screen();
    terminal_hide_cursor();
    
    // Main animation loop
    int frame_delay = 1000 / fps;  // Delay in milliseconds
    int paused = 0;
    
    const char* intensity_names[] = {"Red/Orange", "Classic", "Hot White"};
    printf("DOOM Fire Effect - Press 'q' to quit, SPACE to pause, arrows for wind\n");
    printf("Current: %dx%d, %d FPS, Wind: %d, Mode: %s, Intensity: %s\n", 
           width, height, fps, wind_direction, use_optimized ? "Optimized" : "Standard",
           intensity_names[fire_intensity]);
    SLEEP(2000);  // Show info for 2 seconds
    
    terminal_clear_screen();
    
    while (running) {
        // Handle user input
        handle_input(fire, &paused, &fps, &frame_delay);
        
        if (!paused) {
            // Update fire simulation
            fire_update(fire);
            
            // Render fire
            if (use_optimized) {
                fire_render_optimized(fire);
            } else {
                fire_render(fire);
            }
        }
        
        // Frame rate control
        SLEEP(frame_delay);
    }
    
    // Cleanup
    terminal_cleanup();
    fire_destroy(fire);
    
    printf("Thanks for watching the fire! 🔥\n");
    return 0;
}