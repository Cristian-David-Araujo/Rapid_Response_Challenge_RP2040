/**
 * @file main.c
 * @author Cristian David Araujo and Maverick Sossa Tobon
 * @date 2024-03-16
 */

// Standard libraries
#include "pico/stdlib.h"

//Own header files
#include "display7Seg4D.h"
#include "game.h"

/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {

    //Init the GPIOs for the leds and buttons
    uint8_t leds[3] = {0,9,14}; //Red, Green, Blue
    uint8_t buttons[4] = {22,16,27,17}; //Red, Green, Blue, Start
    game_init(buttons, leds);
    

    //Initialize the 7-segment display 4 digits
    uint8_t enables[4] = {1, 2, 3, 4};
    uint8_t diodes[7] = {5, 6, 10, 11, 12, 7, 8};
    display7Seg4D_init(enables, diodes);

    uint16_t number = 0;

    bool last_state[4] = {false, false, false, false};

     while (true) {
        // Read current states of buttons
        bool current_state[4] = {gpio_get(buttons[0]), gpio_get(buttons[1]), gpio_get(buttons[2]), gpio_get(buttons[3])};

        // Check for rising edge and sum values
        if (current_state[0] && !last_state[0]) {
            number += 1;
        }
        if (current_state[1] && !last_state[1]) {
            number += 10;
        }
        if (current_state[2] && !last_state[2]) {
            number += 100;
        }
        if (current_state[3] && !last_state[3]) {
            number = 0;
        }

        // Update leds according to button states
        gpio_put(leds[0], current_state[0]);
        gpio_put(leds[1], current_state[1]);
        gpio_put(leds[2], current_state[2]);

        // Show number on 7 segment display
        uint64_t actualTime_us = time_us_64();
        display7Seg4D_show(enables, diodes, number, 60, actualTime_us);

        // Save current button states for next iteration
        for (int i = 0; i < 4; i++) {
            last_state[i] = current_state[i];
        }
    }

}