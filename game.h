#ifndef GAME_H
#define GAME_H

#include "pico/stdlib.h"

/**
 * @brief Initialize the pins for the game
 * 
 * @param buttons Array of button pins {R,G,B,START}
 * @param leds Array of led pins {R,G,B}
 */
void game_init(uint8_t buttons[4], uint8_t leds[3]);

#endif // GAME_H