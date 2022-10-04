/*standard library*/
#include <stdio.h>

/*pico-sdk library*/
#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

/*custom library*/
#include "cube.hpp"
#include "numbers.hpp"

#define SET_X(x) gpio_put((x), 0)
#define CLEAR_X(x) gpio_put((x), 1)

#define SET_Y(y) gpio_put((y), 0)
#define CLEAR_Y(y) gpio_put((y), 1)

#define SET_Z(z) gpio_put((z), 1)
#define CLEAR_Z(z) gpio_put((z), 0)

extern const uint8_t X_table[5];
extern const uint8_t Y_table[5];
extern const uint8_t Z_table[5];

uint8_t display_number = 0;

void init_leds()
{
    gpio_init(25U);
    gpio_set_dir(25U, GPIO_OUT);
    gpio_put(25U, 1);
    for(int i = 0; i < 5; i++)
    {
        gpio_init(X_table[i]);
        gpio_init(Y_table[i]);
        gpio_init(Z_table[i]);

        gpio_set_dir(X_table[i], GPIO_OUT);    
        gpio_set_dir(Y_table[i], GPIO_OUT);    
        gpio_set_dir(Z_table[i], GPIO_OUT);

        CLEAR_X(X_table[i]);
        CLEAR_Y(Y_table[i]);
        CLEAR_Z(Z_table[i]);
    }
}

int main()
{
    init_leds();
    cube Cube(125);
    
    while(1)
    {
        switch (display_number)
        {
        case 0:
            zero(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 1:
            one(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 2:
            two(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 3:
            three(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 4:
            four(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 5:
            five(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 6:
            six(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 7:
            seven(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 8:
            eight(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        case 9:
            nine(Cube, X_table[2], 3000);
            if (Cube.get_display_state() == 2)
            {
                Cube.clr_leds();
                Cube.reset_display_state();
                ++display_number;
            }
            break;
        
        default:
            display_number = 0;
            break;
        }
        
    }
    
    return 0;
}


void const testing_main()
{
    // led leds[125];
    // uint8_t led_count = 0;
    cube cube_state(125);

    int a=1, b=1, c=1;
    if (cube_state.get_display_state() == 0)
        {
            cube_state.clr_leds();
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    for (int k = 0; k < c; k++)
                    {
                        cube_state.add_led(X_table[k], Y_table[j], Z_table[i]);
                    }
                }
            }
            if (c < 5)
                ++c;
            else if (b < 5)
            {
                ++b;
            }
            else if (a < 5)
            {
                ++a;
            }
            else
            {
                a = 1;
                b = 1;
                c = 1;
            }
        }
        cube_state.display(500);

        if (cube_state.get_display_state() == 2)
            cube_state.reset_display_state();

}