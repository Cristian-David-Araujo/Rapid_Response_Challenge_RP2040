#include "display7Seg4D.h"

void display7Seg4D_init(uint8_t enables[4], uint8_t diodes[7])
{
    for (int i = 0; i < 4; i++)
    {
        gpio_init(enables[i]);
        gpio_set_dir(enables[i], GPIO_OUT);
    }
    for (int i = 0; i < 7; i++)
    {
        gpio_init(diodes[i]);
        gpio_set_dir(diodes[i], GPIO_OUT);
    }
}

uint8_t *codifyNumber(uint8_t number) {
    static uint8_t diodesON[7]; // static para que persista fuera de la función

    switch (number) {
        case 0:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 0; // E - ON
            diodesON[5] = 0; // F - ON
            diodesON[6] = 1; // G - OFF
            break;

        case 1:
            diodesON[0] = 1; // A - OFF
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 1; // D - OFF
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 1; // F - OFF
            diodesON[6] = 1; // G - OFF
            break;

        case 2:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 1; // C - OFF
            diodesON[3] = 0; // D - ON
            diodesON[4] = 0; // E - ON
            diodesON[5] = 1; // F - OFF
            diodesON[6] = 0; // G - ON
            break;

        case 3:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 1; // F - OFF
            diodesON[6] = 0; // G - ON
            break;

        case 4:
            diodesON[0] = 1; // A - OFF
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 1; // D - OFF
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 0; // F - ON
            diodesON[6] = 0; // G - ON
            break;

        case 5:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 1; // B - OFF
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 0; // F - ON
            diodesON[6] = 0; // G - ON
            break;

        case 6:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 1; // B - OFF
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 0; // E - ON
            diodesON[5] = 0; // F - ON
            diodesON[6] = 0; // G - ON
            break;

        case 7:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 1; // D - OFF
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 1; // F - OFF
            diodesON[6] = 1; // G - OFF
            break;

        case 8:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 0; // E - ON
            diodesON[5] = 0; // F - ON
            diodesON[6] = 0; // G - ON
            break;

        case 9:
            diodesON[0] = 0; // A - ON
            diodesON[1] = 0; // B - ON
            diodesON[2] = 0; // C - ON
            diodesON[3] = 0; // D - ON
            diodesON[4] = 1; // E - OFF
            diodesON[5] = 0; // F - ON
            diodesON[6] = 0; // G - ON
            break;

        default:
            break;
    }

    return diodesON;
}

uint8_t *separateDigits(uint16_t number)
{
    static uint8_t digits[4]; // Array to store the separated digits
    
    // Thousands
    digits[3] = (number / 1000) % 10;
    // Hundreds
    digits[2] = (number / 100) % 10;
    // Tens
    digits[1] = (number / 10) % 10;
    // Units
    digits[0] = number % 10;
    
    return digits;

}

uint8_t *generateEnablesDigit(uint8_t actualDisplay)
{
    static uint8_t enables[4]; // Array to store the enables of the digits

    for (int i = 0; i < 4; i++)
    {
        enables[i] = (i == actualDisplay ? 0 : 1);
    }

    return enables;
}

void display7Seg4D_show(uint8_t enables[4], uint8_t diodes[7], uint16_t number, uint8_t frequency, uint64_t actualTime_us)
{
    static uint64_t lastTime_us;
    static uint8_t actualDisplay;
    frequency *= 4;

    if (actualTime_us - lastTime_us >= ((uint32_t)1000000 / (uint32_t)frequency))
    {
        lastTime_us = actualTime_us;
        uint8_t *enablesDigit = generateEnablesDigit(actualDisplay);
        uint8_t *digits = separateDigits(number);
        uint8_t *diodesON = codifyNumber(digits[actualDisplay]);
        for (int i = 0; i < 4; i++)
        {
            gpio_put(enables[i], enablesDigit[i]);
        }
        for (int i = 0; i < 7; i++)
        {
            gpio_put(diodes[i], diodesON[i]);
        }
        actualDisplay++;
        actualDisplay = actualDisplay  % 4;
    }
}
