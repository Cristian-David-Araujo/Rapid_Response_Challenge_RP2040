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
 * @brief This funtions implements the gameplay. Execute other functions and detect the events
 * 
 * @param buttons 
 * @param leds 
 * @param actualTime_us 
 * @param bestTime 
 * @param start Indicates if the game is running (true) or not (false)
 * @param randLed 
 * @param randWaitTime 
 */
void game_run(uint8_t buttons[4], uint8_t leds[3], uint64_t actualTime_us, 
                uint16_t *bestTime, bool *start, uint8_t *randLed, uint8_t *randWaitTime);

/**
 * @brief Generates the inicial secuence, in which the LEDs will light up in a specific order: 111, 011, 001, 000.
 * 
 * @param leds 
 * @param secuenceFinished bool that indicates whether the inicial secuence is finished (true) or not (false).
 * @param waitTime It will contain the time when the random wait starts.
 * @param actualTime_us It will be asigned to 'waitTime' when the random wait starts.
 */
void generate_secuence(uint8_t leds[3], bool *secuenceFinished, uint32_t *waitTime, uint64_t actualTime_us);

/**
 * @brief Implements an rising edge detector by software for penalizations. 
 * Under certain limitations, it detects a pulse from any button.
 * 
 * @param buttons 
 * @param button_edge 
 * @return true if button was pressed, false other wise.
 */
bool rising_edge_detector(uint8_t buttons[4], bool button_edge[4]);

#endif // GAME_H