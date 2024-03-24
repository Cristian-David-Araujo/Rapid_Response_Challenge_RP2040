#include "game.h"

void game_init(uint8_t buttons[4], uint8_t leds[3])
{
    for (int i = 0; i < 3; i++)
    {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
    }

    for (int i = 0; i < 4; i++)
    {
        gpio_init(buttons[i]);
        gpio_set_dir(buttons[i], GPIO_IN);
        gpio_pull_down(buttons[i]);
        gpio_set_input_hysteresis_enabled(buttons[i], true); // smitt trigger
    }
}

void game_run(uint8_t buttons[4], uint8_t leds[3], uint64_t actualTime_us, uint16_t *bestTime, bool *start)
{
    static uint8_t timePlayer;
    static bool secuenceFinished = false, randomWaitFinished = false;
    *start = true;

    
    if (!secuenceFinished) {
        generate_secuence(leds, &secuenceFinished);
        return;
    }
}

void generate_secuence(uint8_t leds[3], bool *secuenceFinished)
{
    static uint8_t currectState = 0;
    static uint32_t contTime = 0;

    contTime++;
    if (contTime >= 500000)
    {

        if (currectState >= 0) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 1<<leds[2] | 1<<leds[1] | 1<<leds[0]);
        }if (currectState >= 1) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 1
            <<leds[1] | 1<<leds[0]);
        }if (currectState >= 2) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 0<<leds[1] | 1<<leds[0]);
        }if (currectState >= 3) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 0<<leds[1] | 0<<leds[0]);
            *secuenceFinished = true;
            currectState = 4;
        }

        contTime = 0;
        currectState++;
        
    }

}
