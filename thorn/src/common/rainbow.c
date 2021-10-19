#include "common/rainbow.h"

void draw () {
    unsigned int const RB_SIZE   = sizeof (RAINBOW) / sizeof (color);
    unsigned int const X_DIVISOR = GPU_SCREEN_WIDTH / RB_SIZE;
    unsigned int const Y_DIVISOR = GPU_SCREEN_HEIGHT / RB_SIZE;

    unsigned int * rainbow_i = (unsigned int *) RAINBOW;
    unsigned int * fb_i      = (unsigned int *) get_fb ();

    while (1) {
        for (int offset = 0; offset < RB_SIZE; offset++) {
            for (int x = 0; x < GPU_SCREEN_WIDTH - GPU_SCREEN_WIDTH % X_DIVISOR; x++) {
                for (int y = 0; y < GPU_SCREEN_HEIGHT; y++) {
                    fb_i[y * GPU_SCREEN_WIDTH + x] ^= rainbow_i[(x / X_DIVISOR + offset) % RB_SIZE];
                }
            }
            for (int y = 0; y < GPU_SCREEN_HEIGHT - GPU_SCREEN_HEIGHT % Y_DIVISOR; y++) {
                for (int x = 0; x < GPU_SCREEN_WIDTH; x++) {
                    fb_i[y * GPU_SCREEN_WIDTH + x] ^= rainbow_i[(y / Y_DIVISOR + offset) % RB_SIZE];
                }
            }
        }
    }
}
