#include "fire.h"

// DOOM fire color palette - ANSI 256-color codes (Red/Orange focused, less yellow/white)
static const int fire_palette[] = {
    232, // 0  - Black
    233, // 1  - Very dark gray
    234, // 2  - Dark gray
    52,  // 3  - Very dark red
    52,  // 4  - Very dark red
    88,  // 5  - Dark red
    88,  // 6  - Dark red
    124, // 7  - Red
    124, // 8  - Red
    160, // 9  - Red
    160, // 10 - Red
    196, // 11 - Bright red
    196, // 12 - Bright red
    196, // 13 - Bright red
    202, // 14 - Red-orange
    202, // 15 - Red-orange
    202, // 16 - Red-orange
    208, // 17 - Orange
    208, // 18 - Orange
    208, // 19 - Orange
    214, // 20 - Orange
    214, // 21 - Orange
    220, // 22 - Orange-yellow
    220, // 23 - Orange-yellow
    226, // 24 - Yellow-orange
    226, // 25 - Yellow-orange
    227, // 26 - Yellow
    227, // 27 - Yellow
    228, // 28 - Light yellow
    228, // 29 - Light yellow
    229, // 30 - Light yellow
    229, // 31 - Light yellow
    230, // 32 - Very light yellow
    230, // 33 - Very light yellow
    231, // 34 - Nearly white
    231, // 35 - Nearly white
    231  // 36 - White (max intensity)
};

static const int palette_size = sizeof(fire_palette) / sizeof(fire_palette[0]);

Fire* fire_create(int width, int height, int intensity_mode) {
    Fire *fire = malloc(sizeof(Fire));
    if (!fire) {
        return NULL;
    }
    
    fire->width = width;
    fire->height = height;
    fire->size = width * height;
    fire->wind_direction = 0;  // No wind by default
    fire->intensity_mode = intensity_mode;
    
    fire->buffer = calloc(fire->size, sizeof(int));
    if (!fire->buffer) {
        free(fire);
        return NULL;
    }
    
    return fire;
}

void fire_destroy(Fire *fire) {
    if (fire) {
        free(fire->buffer);
        free(fire);
    }
}

void fire_init_source(Fire *fire) {
    if (!fire) return;
    
    int bottom_row_start = (fire->height - 1) * fire->width;
    
    for (int x = 0; x < fire->width; x++) {
        int intensity;
        
        switch (fire->intensity_mode) {
            case 0: // Red/Orange focused (current default)
                intensity = 18 + (rand() % 8);  // Range 18-25
                break;
            case 1: // Classic DOOM (balanced)
                intensity = (MAX_FIRE_INTENSITY - 10) + (rand() % 10);  // Range 26-35
                break;
            case 2: // Hot white flames
                intensity = MAX_FIRE_INTENSITY;  // Always max intensity
                break;
            default:
                intensity = 18 + (rand() % 8);  // Default to red/orange
                break;
        }
        
        fire->buffer[bottom_row_start + x] = intensity;
    }
}

void fire_spread_pixel(Fire *fire, int src_index) {
    int pixel_intensity = fire->buffer[src_index];
    
    if (pixel_intensity == 0) {
        // No fire to spread
        int dest_index = src_index - fire->width;
        if (dest_index >= 0) {
            fire->buffer[dest_index] = 0;
        }
        return;
    }
    
    // Calculate random decay and wind effect
    int random_decay = rand() % 2;  // 0 or 1
    int wind_offset = (rand() % WIND_STRENGTH) * fire->wind_direction;
    
    // Calculate destination pixel with wind effect
    int dest_index = src_index - fire->width + wind_offset;
    
    // Ensure destination is within bounds
    if (dest_index >= 0 && dest_index < fire->size) {
        int new_intensity = pixel_intensity - random_decay;
        fire->buffer[dest_index] = (new_intensity > 0) ? new_intensity : 0;
    }
}

void fire_update(Fire *fire) {
    if (!fire) return;
    
    // Process all pixels except the bottom row (fire source)
    for (int y = 1; y < fire->height; y++) {
        for (int x = 0; x < fire->width; x++) {
            int index = y * fire->width + x;
            fire_spread_pixel(fire, index);
        }
    }
    
    // Occasionally add some randomness to the fire source
    if (rand() % 100 < 10) {  // 10% chance for more variation
        int bottom_row_start = (fire->height - 1) * fire->width;
        int random_x = rand() % fire->width;
        
        int random_intensity;
        switch (fire->intensity_mode) {
            case 0: // Red/Orange focused
                random_intensity = 15 + (rand() % 10);  // Range 15-24
                break;
            case 1: // Classic DOOM
                random_intensity = 20 + (rand() % 15);  // Range 20-34
                break;
            case 2: // Hot white flames
                random_intensity = (MAX_FIRE_INTENSITY - 5) + (rand() % 5);  // Range 31-36
                break;
            default:
                random_intensity = 15 + (rand() % 10);
                break;
        }
        
        fire->buffer[bottom_row_start + random_x] = random_intensity;
    }
}

int get_fire_color(int intensity) {
    if (intensity < 0) intensity = 0;
    if (intensity >= palette_size) intensity = palette_size - 1;
    return fire_palette[intensity];
}

void fire_render(Fire *fire) {
    if (!fire) return;
    
    terminal_move_cursor_home();
    
    for (int y = 0; y < fire->height; y++) {
        for (int x = 0; x < fire->width; x++) {
            int index = y * fire->width + x;
            int intensity = fire->buffer[index];
            int color = get_fire_color(intensity);
            
            // Print colored space character
            printf(ANSI_BG_COLOR " ", color);
        }
        printf(ANSI_RESET_COLOR);
        
        // Only add newline if not the last row to prevent scrolling
        if (y < fire->height - 1) {
            printf("\n");
        }
    }
    fflush(stdout);
}

void fire_render_optimized(Fire *fire) {
    if (!fire) return;
    
    terminal_move_cursor_home();
    
    // Render using Unicode half-blocks for double vertical resolution
    for (int y = 0; y < fire->height - 1; y += 2) {
        for (int x = 0; x < fire->width; x++) {
            int top_index = y * fire->width + x;
            int bottom_index = (y + 1) * fire->width + x;
            
            int top_intensity = fire->buffer[top_index];
            int bottom_intensity = fire->buffer[bottom_index];
            
            int top_color = get_fire_color(top_intensity);
            int bottom_color = get_fire_color(bottom_intensity);
            
            // Use lower half block with top color as foreground, bottom as background
            printf("\033[38;5;%dm\033[48;5;%dm▄", top_color, bottom_color);
        }
        printf(ANSI_RESET_COLOR);
        
        // Only add newline if not the last row to prevent scrolling
        if (y < fire->height - 3) {
            printf("\n");
        }
    }
    
    // Handle odd height case
    if (fire->height % 2 == 1) {
        int y = fire->height - 1;
        for (int x = 0; x < fire->width; x++) {
            int index = y * fire->width + x;
            int intensity = fire->buffer[index];
            int color = get_fire_color(intensity);
            printf(ANSI_BG_COLOR " ", color);
        }
        printf(ANSI_RESET_COLOR);
    }
    
    fflush(stdout);
}
