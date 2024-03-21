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
        gpio_set_input_hysteresis_enabled(buttons[i], true);
    }
}
