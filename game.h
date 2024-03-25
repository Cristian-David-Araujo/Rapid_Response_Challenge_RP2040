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

/**
 * @brief 
 * 
 * @param buttons 
 * @param leds 
 * @param actualTime_us 
 * @param bestTime 
 */
void game_run(uint8_t buttons[4], uint8_t leds[3], uint64_t actualTime_us, 
                uint16_t *bestTime, bool *start, uint8_t *randLed, uint8_t *randWaitTime);

/**
 * @brief 
 * 
 * @param led 
 * @param actualTime_us 
 */
void generate_secuence(uint8_t leds[3], bool *secuence, uint32_t *waitTime, uint64_t actualTime_us);

bool rising_edge_detector(uint8_t buttons[4], bool button_edge[4]);

#endif // GAME_H