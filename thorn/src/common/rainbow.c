#include "common/rainbow.h"

void draw () {
    populate_rainbow ();
    
    unsigned int const X_DIVISOR = GPU_SCREEN_WIDTH / RB_SIZE;
    unsigned int const Y_DIVISOR = GPU_SCREEN_HEIGHT / RB_SIZE;
    
    unsigned int * rainbow_i = (unsigned int *) rainbow;
    unsigned int * fb_i = (unsigned int *) get_fb ();
    
    color current = rainbow[0];
    unsigned int current_i = * (unsigned int *) & current;
    
    while (1) {
        for (int offset = 0; offset < OFFSET_STEPS; offset++) {
            for (int x = 0; x < GPU_SCREEN_WIDTH - GPU_SCREEN_WIDTH % X_DIVISOR; x++) {
                for (int y = 0; y < GPU_SCREEN_HEIGHT; y++) {
                    fb_i[y * GPU_SCREEN_WIDTH + x] ^= rainbow_i[(x / X_DIVISOR + OFFSET_FACTOR * offset) % RB_SIZE];
                }
            }
            for (int y = 0; y < GPU_SCREEN_HEIGHT - GPU_SCREEN_HEIGHT % Y_DIVISOR; y++) {
                for (int x = 0; x < GPU_SCREEN_WIDTH; x++) {
                    fb_i[y * GPU_SCREEN_WIDTH + x] ^= rainbow_i[(y / Y_DIVISOR + OFFSET_FACTOR * offset) % RB_SIZE];
                }
            }
        }
    }
}

void populate_rainbow () {
    unsigned char red = 0xFF;
    unsigned char green = 0x00;
    unsigned char blue = 0xFF;
    
    do { // purple to red
        write_color_to_rainbow (red, green, blue);
    } while (blue -= 4 > 3);
    
    do { // red to yellow
        write_color_to_rainbow (red, green += 4, blue);
    } while (green < 252);
    
    do { // yellow to green
        write_color_to_rainbow (red, green, blue);
    } while (red -= 4 > 3);
    
    do { // green to cyan
        write_color_to_rainbow (red, green, blue += 4);
    } while (blue < 252);
    
    do { // cyan to blue
        write_color_to_rainbow (red, green, blue);
    } while (green -= 4 > 3);
    
    do { // blue to purple
        write_color_to_rainbow (red += 4, green, blue);
    } while (red < 252);
    
}

int write_color_to_rainbow (unsigned char red, unsigned char green, unsigned char blue) {
    static int index = 0;
    rainbow[index].red = red;
    rainbow[index].green = green;
    rainbow[index].blue = blue;
    printf ("%d ", index);
    return ++index;
}
