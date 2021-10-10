#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// The built in LED
#define LED_PIN 8

int main() {
    stdio_init_all();
    getchar_timeout_us(1);

    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);

    pwm_set_wrap(slice_num, 250);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    pwm_set_enabled(slice_num, true);

    int input_char;
    bool demo_mode = true;
    uint i = 1;
    bool up = true;
    uint to_display = 0;
    while (true) {
        input_char = getchar_timeout_us(demo_mode ? 2000 : 10000000);
        if (input_char == -1) {
            if (up) {
                i++;
                if (i >= 250) {
                    up = !up;
                }
            } else if (!up) {
                i--;
                if (i <= 0) {
                    up = !up;
                }
            }
            to_display = i;
            demo_mode = true;
        } else {
            to_display = input_char;
            demo_mode = false;
        }
        pwm_set_chan_level(slice_num, PWM_CHAN_B, to_display);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, to_display);

    }
}