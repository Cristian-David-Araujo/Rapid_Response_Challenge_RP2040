/**
 * @file main.c
 * @author Cristian David Araujo and Maverick Sossa Tobon
 * @date 2024-03-16
 */

// Standard libraries
#include "pico/stdlib.h"
#include "pico/time.h"

//Own header files
#include "display7Seg4D.h"

/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {

    // Init the seed to random
    // srand(time()); // This function initializes the MCU and does an infinite cycle.

    //Init the GPIOs for the leds and buttons
    uint8_t leds[3] = {0,9,14}; //Red, Green, Blue
    uint8_t buttons[4] = {22,16,27,17}; //Red, Green, Blue, Start
    game_init(buttons, leds);

    //Initialize the 7-segment display 4 digits
    uint8_t enables[4] = {1, 2, 3, 4};
    uint8_t diodes[7] = {5, 6, 10, 11, 12, 7, 8};
    display7Seg4D_init(enables, diodes);

    // Generate random: led and wait time
    uint8_t randLed = time_us_32() % 3;
    uint8_t randWaitTime = time_us_32() % 10 + 1;

    uint16_t bestTime = 0;

    bool last_state[4] = {false, false, false, false};
    bool start = false;

     while (true) {
        
        // Show number on 7 segment display
        uint64_t actualTime_us = time_us_64();
        display7Seg4D_show(enables, diodes, bestTime, 60, actualTime_us);

        //Run the game
        if (gpio_get(buttons[3]) || start){
            game_run(buttons, leds, actualTime_us, &bestTime, &start, &randLed, &randWaitTime);
        }

    }

}