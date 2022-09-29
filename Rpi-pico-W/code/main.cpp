/*standard library*/
#include <stdio.h>

/*pico-sdk library*/
#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

/*custom library*/
#include "cube.hpp"


#define SET_X(x) gpio_put((x), 0)
#define CLEAR_X(x) gpio_put((x), 1)

#define SET_Y(y) gpio_put((y), 0)
#define CLEAR_Y(y) gpio_put((y), 1)

#define SET_Z(z) gpio_put((z), 1)
#define CLEAR_Z(z) gpio_put((z), 0)

uint8_t X_table[5] = {X0, X1, X2, X3, X4};
uint8_t Y_table[5] = {Y0, Y1, Y2, Y3, Y4};
uint8_t Z_table[5] = {Z0, Z1, Z2, Z3, Z4};


int main()
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
    // led leds[125];
    // uint8_t led_count = 0;
    cube cube_state(125);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cube_state.add_leds(X_table[k], Y_table[j], Z_table[i]);
            }
        }
    }

    while(1)
    {
        cube_state.display();
    }
    
    return 0;
}