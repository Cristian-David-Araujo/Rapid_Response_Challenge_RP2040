#ifndef DISPLAY7SEG4D_H
#define DISPLAY7SEG4D_H

#include "pico/stdlib.h"

/**
 * @brief Initialize all pins to be used for the 4-digit 7-segment display module of the common anode.
 * 
 * @param enables Array with the gpio numbers of the enables of each digit in little endian 
 * @param diodes Array with the numbers of the diode gpio's that will be corresponding (A, B, C, D, E, F, G)  
 * @return void 
 */
void display7Seg4D_init(uint8_t enables[4], uint8_t diodes[7]);

/**
 * @brief Codify a number to be shown in the 7-segment display of the common anode.
 * 
 * @param number input number to be codified for showing in the 7-segment display
 * @return uint8_t* array with the diodes that will be ON or OFF for showing the number in the 7-segment display
 */
uint8_t* codifyNumber(uint8_t number);

/**
 * @brief Separate the digits of a number to be shown in the 7-segment display
 * 
 * @param number input number to be separated in digits
 * @return uint8_t* array with the digits of the input number
 */
uint8_t* separateDigits(uint16_t number);


/**
 * @brief Generate a array with the enables of the digits of the 7-segment display
 * 
 * @param actualDisplay actual digit to be shown
 * @return uint8_t* 
 */
uint8_t* generateEnablesDigit(uint8_t actualDisplay);

/**
 * @brief It is responsible for displaying the best time on the 7-segment displays.
 * 
 * @param enables Array with the gpio numbers of the enables of each digit in little endian
 * @param diodes Array with the numbers of the diode gpio's that will be corresponding (A, B, C, D, E, F, G)
 * @param number number to show in module
 * @param frequency frequency of refresh of the display in Hz
 * @param actualTime_us time counter of RP2040 in microseconds
 */
void display7Seg4D_show(uint8_t enables[4], uint8_t diodes[7], uint16_t number, uint8_t frequency, uint64_t actualTime_us);

#endif