#include "common/temperature.h"

bool init_temperature () {
    {                                                       // Read out maximum temperature
        int c = 0;                                          // Message size; increment while we write
        temperature_request[++c] = 0;                       // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
        temperature_request[++c] = 0x0003000a;              // Tag to get maximum temperature
        temperature_request[++c] = 4;                       // Size of value buffer
        temperature_request[++c] = 0;                       // Response & value buffer size written will be written here
        temperature_request[++c] = 0;                       // Temperature (device?) ID, should stay 0
        temperature_request[++c] = 0;                       // Will be overwritten by maximum temperature
        int index_max_temperature = c;
        
        temperature_request[++c] = 0;                       // End tag
        
        temperature_request[0] = (4 * ++c);                 // Write message size at the beginning of the buffer
        
        // If reading maximum temperature fails, keep default
        if (!mailbox_request (temperature_request, PROPERTY_ARM_VC)) return false;
        // Else update temperature
        max_temperature = temperature_request[index_max_temperature] ? : TEMPERATURE_MAX;
        
        return true;        // TODO: remove
    }
    
    // Start regulate_temperature service here
}

void regulate_temperature () {
    static int previous_temperature = TEMPERATURE_SHOULD;
    int current = get_temperature ();
    printf ("\rCurrent temperature: %d °C", current / 1000);
}

int get_max_temperature () {
    return max_temperature;
}

int get_temperature () {
    {                                                       // Read out current temperature
        int c = 0;                                          // Message size; increment while we write
        temperature_request[++c] = 0;                       // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
        temperature_request[++c] = 0x00030006;              // Tag to get current temperature
        temperature_request[++c] = 0;                       // Size of value buffer
        temperature_request[++c] = 4;                       // Response & value buffer size written will be written here
        temperature_request[++c] = 0;                       // Temperature (device?) ID, should stay 0
        temperature_request[++c] = 0;                       // Will be overwritten by current temperature
        int index_temperature = c;
        
        temperature_request[++c] = 0;                       // End tag
        
        temperature_request[0] = (4 * ++c);                 // Write message size at the beginning of the buffer
        
        // If reading maximum temperature fails, keep default
        if (!mailbox_request (temperature_request, PROPERTY_ARM_VC)) return -1;
        // Else update temperature
        max_temperature = temperature_request[index_temperature] ? : TEMPERATURE_MAX;
        return temperature_request[index_temperature];
    }
}