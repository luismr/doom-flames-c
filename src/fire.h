#ifndef FIRE_H
#define FIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

// Platform detection
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <sys/select.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

// Fire configuration constants
#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 40
#define MAX_FIRE_INTENSITY 36
#define FRAME_DELAY_MS 33  // ~30 FPS
#define WIND_STRENGTH 3    // Maximum horizontal shift for wind effect

// ANSI escape codes
#define ANSI_CLEAR_SCREEN "\033[2J"
#define ANSI_CURSOR_HOME "\033[H"
#define ANSI_HIDE_CURSOR "\033[?25l"
#define ANSI_SHOW_CURSOR "\033[?25h"
#define ANSI_RESET_COLOR "\033[0m"
#define ANSI_BG_COLOR "\033[48;5;%dm"

// Fire structure
typedef struct {
    int *buffer;
    int width;
    int height;
    int size;
    int wind_direction;  // -1 left, 0 none, 1 right
    int intensity_mode;  // 0=red/orange, 1=classic, 2=hot white
} Fire;

// Function declarations

// Fire algorithm functions
Fire* fire_create(int width, int height, int intensity_mode);
void fire_destroy(Fire *fire);
void fire_init_source(Fire *fire);
void fire_update(Fire *fire);
void fire_spread_pixel(Fire *fire, int src_index);

// Terminal functions
int terminal_init(void);
void terminal_cleanup(void);
void terminal_get_size(int *width, int *height);
void terminal_clear_screen(void);
void terminal_hide_cursor(void);
void terminal_show_cursor(void);
void terminal_move_cursor_home(void);
void terminal_move_cursor_to(int row, int col);

// Rendering functions
void fire_render(Fire *fire);
void fire_render_optimized(Fire *fire);  // Using Unicode half-blocks
int get_fire_color(int intensity);

// Signal handling
void setup_signal_handlers(void);
void signal_handler(int sig);

// Input handling
int kbhit(void);
int getch_nonblocking(void);
int read_key_sequence(void);

// Global variables
extern volatile int running;
extern Fire *global_fire;

#endif // FIRE_H