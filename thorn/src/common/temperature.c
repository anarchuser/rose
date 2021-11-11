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
    while (1) {
        delay (TEMPERATURE_CHECK_DELAY);
        unsigned int previous                   = temperatures[current_temperature_index];
        current_temperature_index               = (current_temperature_index + 1) % TEMPERATURE_POINTS;
        temperatures[current_temperature_index] = get_temperature ();
        unsigned int current                    = temperatures[current_temperature_index];

        if (current >= TEMPERATURE_FAN_ON) {
            set_fan (1);
        } else if (current <= TEMPERATURE_FAN_OFF) {
            set_fan (0);
        }

        previous = (previous + 50) / 100 * 100;
        current  = (current + 50) / 100 * 100;
        printf ("\rCurrent temperature: %d,%d C. Change since last iteration: %d mC    ", current / 1000, current % 1000 / 100, current - previous);

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
    // Corners of graph
    point_t OO = {0, get_max_height () / 2};
    point_t OY = {0, get_max_height ()};
    point_t XO = {get_max_width (), get_max_height () / 2};
    point_t XY = {get_max_width (), get_max_height ()};

    // Clear lower half of screen
    unsigned int  pitch = get_fb_info ()->pitch;
    unsigned int  size  = get_fb_info ()->fb_size;
    unsigned long fb    = (unsigned long) get_fb ();
    memzero (fb + size / 8 * 4 - 7 * pitch, size / 4 - 5 * pitch);
    memzero (fb + size / 8 * 6 - 11 * pitch, size / 8 - 3 * pitch);
    memzero (fb + size / 8 * 7 - 13 * pitch, size / 8 - 22 * pitch);

    // Draw frame, legend and orientation lines
    drawline_grid ((point_t) {0, get_max_height () / 8 * 6}, (point_t) {get_max_width (), get_max_height () / 8 * 6}, (color_t) {0, 128, 255, 0});
    drawline_grid ((point_t) {0, get_max_height () / 8 * 7}, (point_t) {get_max_width (), get_max_height () / 8 * 7}, (color_t) {0, 128, 0, 0});

    drawline_grid ((point_t) {0, get_max_height () / 8 * 4}, (point_t) {get_max_width (), get_max_height () / 8 * 4}, (color_t) {255, 128, 0, 0});
    drawline_grid ((point_t) {4 * FONT_REAL_WIDTH, get_max_height () / 8 * 8}, (point_t) {get_max_width (), get_max_height () / 8 * 8}, (color_t) {255, 128, 0, 0});

    char buf[5] = {0};
    sprintf (buf, "%d C", TEMPERATURE_GRAPH_HIGH / 1000);
    prints_location (POINT (OO.x, OO.y - FONT_REAL_WIDTH - 3), buf);
    sprintf (buf, "%d C", TEMPERATURE_GRAPH_LOW / 1000);
    prints_location ((point_t) {OY.x, OY.y - FONT_REAL_WIDTH}, buf);

    // Draw lines between data points
    color_t const red       = {0, 0, 255, 0};
    color_t const blue      = {196, 0, 0, 0};
    int           factor_x  = get_fb_info ()->virtual_width / TEMPERATURE_POINTS;
    int           divisor_y = (TEMPERATURE_GRAPH_HIGH - TEMPERATURE_GRAPH_LOW) / (get_fb_info ()->virtual_height / 2);
    color_t       current   = red;
    for (int j = 0; j < TEMPERATURE_POINTS; j++) {
        unsigned int i0 = (current_temperature_index + j + 1) % TEMPERATURE_POINTS;
        unsigned int i1 = (i0 + 1) % TEMPERATURE_POINTS;
        if (!temperatures[i0] || !temperatures[i1])
            continue;
        if (temperatures[i0] >= TEMPERATURE_FAN_ON)
            current = red;
        else if (temperatures[i0] <= TEMPERATURE_FAN_OFF)
            current = blue;
        point_t a = {j * factor_x, OY.y - (temperatures[i0] - TEMPERATURE_GRAPH_LOW) / divisor_y};
        point_t b = {(j + 1) * factor_x, OY.y - (temperatures[i1] - TEMPERATURE_GRAPH_LOW) / divisor_y};
        drawline (a, b, current);
    }
}