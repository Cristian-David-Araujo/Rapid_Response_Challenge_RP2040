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

void game_run(uint8_t buttons[4], uint8_t leds[3], uint64_t actualTime_us, 
                uint16_t *bestTime, bool *start, uint8_t *randLed, uint8_t *randWaitTime)
{
    static uint32_t timePlayer;
    static uint32_t waitTime;
    static uint8_t penalizations = 0;
    static bool button_edge[4] = {false, false, false, false};
    static bool secuenceFinished = false, randomWaitFinished = false;
    *start = true;

    
    if (!secuenceFinished) {
        generate_secuence(leds, &secuenceFinished, &waitTime, actualTime_us);
        return;
    }else if ((actualTime_us - waitTime) >= *(randWaitTime)*1000000 && !randomWaitFinished) {
        randomWaitFinished = true;
        gpio_put(leds[*randLed], true);
        timePlayer = actualTime_us;
        return;
    }else if (rising_edge_detector(buttons, button_edge) && randomWaitFinished) {
        if (button_edge[*randLed]) {
            gpio_put(leds[*randLed], false);
            uint16_t time_ms = (actualTime_us - timePlayer) / 1000;
            *bestTime = penalizations;
            // if (time_ms < *bestTime || *bestTime == 0) {
            //     *bestTime = time_ms ;
            // }
            secuenceFinished = false;
            randomWaitFinished = false;
            penalizations = 0;
            for (int i = 0; i < 4; i++){
                button_edge[i] = false;
            }
            *start = false;
            *randLed = time_us_32() % 3;
            *randWaitTime = time_us_32() % 10 + 1;
            return;
        }else {
            penalizations++;
            return;
        }
    }

}

void generate_secuence(uint8_t leds[3], bool *secuenceFinished, uint32_t *waitTime, uint64_t actualTime_us)
{
    static uint8_t currectState = 0;
    static uint64_t contTime = 0;

    contTime++;
    if (contTime >= 500000)
    {
        if (currectState >= 0) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 1<<leds[2] | 1<<leds[1] | 1<<leds[0]);
        }if (currectState >= 1) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 1<<leds[1] | 1<<leds[0]);
        }if (currectState >= 2) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 0<<leds[1] | 1<<leds[0]);
        }if (currectState >= 3) {
            gpio_put_masked(1<<leds[2] | 1<<leds[1] | 1<<leds[0], 0<<leds[2] | 0<<leds[1] | 0<<leds[0]);
            *secuenceFinished = true;
            *waitTime = actualTime_us;
            currectState = 0;
            contTime = 0;
            return;
        }
        contTime = 0;
        currectState++;
    }
}

bool rising_edge_detector(uint8_t buttons[4], bool button_edge[4])
{
    static bool last_state[4] = {false, false, false, false};
    for (int i = 0; i < 4; i++) {

        if (gpio_get(buttons[i]) && !last_state[i]) {
            last_state[i] = true;
            return true;
        }else if (!gpio_get(buttons[i])) {
            last_state[i] = false;
        }
    }
    return false;
}
