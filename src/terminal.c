#include "fire.h"

// Global variables for signal handling
volatile int running = 1;
Fire *global_fire = NULL;

#ifdef _WIN32
static HANDLE hConsole;
static DWORD originalConsoleMode;
static CONSOLE_SCREEN_BUFFER_INFO originalConsoleInfo;
#else
static struct termios original_termios;
static int termios_saved = 0;
#endif

int terminal_init(void) {
#ifdef _WIN32
    // Windows terminal initialization
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return 0;
    }
    
    // Save original console mode
    if (!GetConsoleMode(hConsole, &originalConsoleMode)) {
        return 0;
    }
    
    // Save original console screen buffer info
    if (!GetConsoleScreenBufferInfo(hConsole, &originalConsoleInfo)) {
        return 0;
    }
    
    // Enable virtual terminal processing for ANSI escape codes
    DWORD newConsoleMode = originalConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, newConsoleMode)) {
        // Try to continue without VT processing (might not work on older Windows)
        fprintf(stderr, "Warning: Could not enable ANSI escape codes. Colors may not work.\n");
    }
    
    return 1;
#else
    // Unix-like systems (macOS, Linux)
    // Check if we have a terminal (not piped input/output)
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
        // Non-interactive mode - skip terminal setup
        termios_saved = 0;
        return 1;
    }
    
    // Save original terminal settings
    if (tcgetattr(STDIN_FILENO, &original_termios) != 0) {
        // If we can't get terminal attributes, continue anyway
        termios_saved = 0;
        return 1;
    }
    termios_saved = 1;
    
    // Set terminal to raw mode for better control
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);  // Disable echo and canonical mode
    raw.c_cc[VMIN] = 0;   // Non-blocking read
    raw.c_cc[VTIME] = 0;  // No timeout
    
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) != 0) {
        // If we can't set raw mode, continue anyway
        termios_saved = 0;
    }
    
    return 1;
#endif
}

void terminal_cleanup(void) {
    // Show cursor and reset colors
    terminal_show_cursor();
    printf(ANSI_RESET_COLOR);
    
#ifdef _WIN32
    // Restore original console mode
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleMode(hConsole, originalConsoleMode);
        
        // Clear screen and reset cursor
        system("cls");
    }
#else
    // Restore original terminal settings
    if (termios_saved) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
    }
    
    // Clear screen
    printf(ANSI_CLEAR_SCREEN ANSI_CURSOR_HOME);
#endif
    
    fflush(stdout);
}

void terminal_get_size(int *width, int *height) {
    *width = DEFAULT_WIDTH;
    *height = DEFAULT_HEIGHT;
    
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        *width = ws.ws_col;
        *height = ws.ws_row;
    }
#endif
    
    // Ensure minimum size
    if (*width < 20) *width = 20;
    if (*height < 10) *height = 10;
    
    // Ensure maximum reasonable size
    if (*width > 200) *width = 200;
    if (*height > 100) *height = 100;
}

void terminal_clear_screen(void) {
    printf(ANSI_CLEAR_SCREEN);
    fflush(stdout);
}

void terminal_hide_cursor(void) {
    printf(ANSI_HIDE_CURSOR);
    fflush(stdout);
}

void terminal_show_cursor(void) {
    printf(ANSI_SHOW_CURSOR);
    fflush(stdout);
}

void terminal_move_cursor_home(void) {
    printf(ANSI_CURSOR_HOME);
}

void terminal_move_cursor_to(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void signal_handler(int sig) {
    (void)sig;  // Suppress unused parameter warning
    running = 0;
    
    // Cleanup and exit gracefully
    terminal_cleanup();
    if (global_fire) {
        fire_destroy(global_fire);
    }
    exit(0);
}

void setup_signal_handlers(void) {
    // Handle Ctrl+C (SIGINT) and other termination signals
    signal(SIGINT, signal_handler);
    
#ifndef _WIN32
    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
#endif
}

// Utility function to check if a key was pressed (non-blocking)
int kbhit(void) {
#ifdef _WIN32
    return _kbhit();
#else
    // Check if we're in interactive mode
    if (!isatty(STDIN_FILENO)) {
        // Non-interactive mode - check if input is available
        int ch = getchar();
        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }
    
    // Interactive mode - use select() for non-blocking check
    fd_set readfds;
    struct timeval timeout;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0;
#endif
}

// Get a character without waiting (non-blocking)
int getch_nonblocking(void) {
#ifdef _WIN32
    if (_kbhit()) {
        return _getch();
    }
    return -1;
#else
    if (!isatty(STDIN_FILENO)) {
        // Non-interactive mode - read directly
        return getchar();
    }
    
    // Interactive mode - read single character
    if (kbhit()) {
        return getchar();
    }
    return -1;
#endif
}

// New function to read escape sequences properly
int read_key_sequence(void) {
#ifdef _WIN32
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 224) {  // Extended key prefix on Windows
            ch = _getch();
            switch (ch) {
                case 72: return 1001;  // Up arrow
                case 80: return 1002;  // Down arrow
                case 77: return 1003;  // Right arrow
                case 75: return 1004;  // Left arrow
            }
        }
        return ch;
    }
    return -1;
#else
    if (!isatty(STDIN_FILENO)) {
        // Non-interactive mode - read directly
        return getchar();
    }
    
    // Interactive mode - try to read escape sequences
    if (kbhit()) {
        char buffer[4];
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
        
        if (bytes_read <= 0) {
            return -1;
        }
        
        // Single character
        if (bytes_read == 1) {
            return (unsigned char)buffer[0];
        }
        
        // Check for escape sequences
        if (bytes_read >= 3 && buffer[0] == 27 && buffer[1] == '[') {
            switch (buffer[2]) {
                case 'A': return 1001;  // Up arrow
                case 'B': return 1002;  // Down arrow
                case 'C': return 1003;  // Right arrow
                case 'D': return 1004;  // Left arrow
            }
        }
        
        // If it starts with ESC but isn't a recognized sequence, return ESC
        if (buffer[0] == 27) {
            return 27;
        }
        
        // Return the first character for other multi-byte sequences
        return (unsigned char)buffer[0];
    }
    return -1;
#endif
}
