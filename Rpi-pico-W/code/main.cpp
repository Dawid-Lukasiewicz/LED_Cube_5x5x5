/*standard library*/
#include <stdio.h>

/*pico-sdk library*/
#include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

/*custom library*/
#include "cube_states.hpp"

#define X0 15U
#define X1 13U
#define X2 12U
#define X3 11U
#define X4 10U

#define Y0 14U
#define Y1 16U
#define Y2 17U
#define Y3 18U
#define Y4 19U

#define Z0 27U
#define Z1 26U
#define Z2 22U
#define Z3 21U
#define Z4 20U

#define SET_X(x) gpio_put((x), 0)
#define CLEAR_X(x) gpio_put((x), 1)

#define SET_Y(y) gpio_put((y), 0)
#define CLEAR_Y(y) gpio_put((y), 1)

#define SET_Z(z) gpio_put((z), 1)
#define CLEAR_Z(z) gpio_put((z), 0)

coordX X_table[5] = {X0, X1, X2, X3, X4};
coordY Y_table[5] = {Y0, Y1, Y2, Y3, Y4};
coordZ Z_table[5] = {Z0, Z1, Z2, Z3, Z4};


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

    while(1)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    set_LED(X_table[i]);
                    set_LED(Y_table[j]);
                    set_LED(Z_table[k]);
                    sleep_ms(25);
                    clr_LED(X_table[i]);
                    clr_LED(Y_table[j]);
                    clr_LED(Z_table[k]);
                    // sleep_ms(0);

                    // SET_X(X_table[i]);
                    // SET_Y(Y_table[j]);
                    // SET_Z(Z_table[k]);
                    // sleep_ms(50);
                    // CLEAR_X(X_table[i]);
                    // CLEAR_Y(Y_table[j]);
                    // CLEAR_Z(Z_table[k]);
                    // sleep_ms(50);
                }
                
            }
            
        }
        
    }
    
    return 0;
}