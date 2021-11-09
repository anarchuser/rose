#include "common/temperature.h"

bool init_temperature () {
    gpio_mode (GPIO_FAN, GPIO_OUTPUT);
    {                                // Read out maximum temperature
        int c                    = 0;// Message size; increment while we write
        temperature_request[++c] = 0;// Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

        temperature_request[++c]  = 0x0003000a;// Tag to get maximum temperature
        temperature_request[++c]  = 8;         // Size of value buffer
        temperature_request[++c]  = 0;         // Response & value buffer size written will be written here
        temperature_request[++c]  = 0;         // Temperature (device?) ID, should stay 0
        temperature_request[++c]  = 0;         // Will be overwritten by maximum temperature
        int index_max_temperature = c;

        temperature_request[++c] = 0;// End tag

        temperature_request[0] = (4 * ++c);// Write message size at the beginning of the buffer

        // If reading maximum temperature fails, keep default
        if (!mailbox_request (temperature_request, PROPERTY_ARM_VC))
            return false;
        // Else update temperature
        max_temperature = temperature_request[index_max_temperature] ?: TEMPERATURE_MAX;
    }

    // Start regulate_temperature service here
    copy_process (PF_KTHREAD, (unsigned long) &regulate_temperature, 0, 0);
    return true;
}

void regulate_temperature () {
    static int previous = TEMPERATURE_SHOULD;
    while (1) {
        delay (TEMPERATURE_CHECK_DELAY);
        int current = get_temperature ();
        printf ("\rCurrent temperature: %d C. Change since last iteration: %d mC    ", current / 1000,
                ((current - previous) + 50) / 500 * 500);

        if (current >= TEMPERATURE_SHOULD) {
            set_fan (1);
        } else if (current < TEMPERATURE_SHOULD - 2000) {
            set_fan (0);
        }
        previous = current;

        draw_temp_graph ();
    }
}

int get_max_temperature () {
    return max_temperature;
}

int get_temperature () {
    {                                // Read out current temperature
        int c                    = 0;// Message size; increment while we write
        temperature_request[++c] = 0;// Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

        temperature_request[++c] = 0x00030006;// Tag to get current temperature
        temperature_request[++c] = 8;         // Size of value buffer
        temperature_request[++c] = 4;         // Response & value buffer size written will be written here
        temperature_request[++c] = 0;         // Temperature (device?) ID, should stay 0
        temperature_request[++c] = 0;         // Will be overwritten by current temperature
        int index_temperature    = c;

        temperature_request[++c] = 0;// End tag

        temperature_request[0] = (4 * ++c);// Write message size at the beginning of the buffer

        // If reading maximum temperature fails, keep default
        if (!mailbox_request (temperature_request, PROPERTY_ARM_VC))
            return max_temperature;
        // Else return temperature
        return temperature_request[index_temperature];
    }
}

void set_fan (bool enable) {
    gpio_set (GPIO_FAN, !enable);
}

void draw_temp_graph () {
    // Clear lower half of screen
    memzero (get_fb () + get_fb_info ()->fb_size / 2, get_fb_info ()->fb_size / 2);

    // Corners of graph
    point_t OO = {0, get_fb_info ()->virtual_height / 2};
    point_t OY = {0, get_fb_info ()->virtual_height - 1};
    point_t XO = {get_fb_info ()->virtual_width - 1, get_fb_info ()->virtual_height / 2};
    point_t XY = {get_fb_info ()->virtual_width - 1, get_fb_info ()->virtual_height - 1};

    // Draw frame + legend
    drawrec (OO, XY, (color_t) {0xFF, 0xFF, 0x00, 0});
    prints_location (OO, "55C");
    prints_location ((point_t) {OY.x, OY.y - FONT_REAL_WIDTH}, "45C");
}