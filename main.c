/**
 * @file main.c
 * @author Cristian David Araujo and Maverick Sossa Tobon
 * @date 2024-03-16
 */

// Standard libraries
#include "pico/stdlib.h"

//Own header files
#include "display7Seg4D.h"

/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
    const uint LED_R = 0;
    const uint LED_G = 9;
    const uint LED_B = 14;
    
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    const uint BUTTON_R = 22;
    const uint BUTTON_G = 16;
    const uint BUTTON_B = 27;

    gpio_init(BUTTON_R);
    gpio_set_dir(BUTTON_R, GPIO_IN);
    gpio_pull_down(BUTTON_R);
    gpio_init(BUTTON_G);
    gpio_set_dir(BUTTON_G, GPIO_IN);
    gpio_pull_down(BUTTON_G);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);

    //Initialize the 7-segment display 4 digits
    uint8_t enables[4] = {1, 2, 3, 4};
    uint8_t diodes[7] = {5, 6, 10, 11, 12, 7, 8};
    display7Seg4D_init(enables, diodes);

    uint16_t number = 0;

    bool last_state_R = false;
    bool last_state_G = false;
    bool last_state_B = false;

     while (true) {
        // Read current states of buttons
        bool current_state_R = gpio_get(BUTTON_R);
        bool current_state_G = gpio_get(BUTTON_G);
        bool current_state_B = gpio_get(BUTTON_B);

        // Check for rising edge and sum values
        if (current_state_R && !last_state_R) {
            number += 1;
        }
        if (current_state_G && !last_state_G) {
            number += 10;
        }
        if (current_state_B && !last_state_B) {
            number += 100;
        }

        // Update LEDs according to button states
        gpio_put(LED_R, current_state_R);
        gpio_put(LED_G, current_state_G);
        gpio_put(LED_B, current_state_B);

        // Show number on 7 segment display
        uint64_t actualTime_us = time_us_64();
        display7Seg4D_show(enables, diodes, number, 60, actualTime_us);

        // Save current button states for next iteration
        last_state_R = current_state_R;
        last_state_G = current_state_G;
        last_state_B = current_state_B;
    }

}