#include "animations.hpp"

#include <cstdlib>
#include <ctime>

typedef uint8_t flag;

void random_led(cube &Cube)
{
    if (Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
        Cube.reset_display_state();
    }
    if (Cube.get_display_state() == 0)
    {
        uint8_t x = std::rand() % MAX_LEDS_X;
        uint8_t y = std::rand() % MAX_LEDS_Y;
        uint8_t z = std::rand() % MAX_LEDS_Z;

        Cube.add_led(X_table[x], Y_table[y], Z_table[z]);
    }
    Cube.display(500);
}

void rain(cube &Cube)
{
    static int8_t z;
    static flag another_drop;
    // uint rain_time_drop_ms = 100000;
    uint rain_time_drop_ms = 100;
    if (Cube.get_display_state() == DISPLAY_STATE_INIT 
        || another_drop)
    {
        another_drop = 0;

        Cube.clr_leds();
        z = 4;
        uint8_t x = std::rand() % MAX_LEDS_X;
        uint8_t y = std::rand() % MAX_LEDS_Y;

        Cube.add_led(X_table[x], Y_table[y], Z_table[z]);
        Cube.__public_time = get_absolute_time();
    }
    // else if (absolute_time_diff_us(Cube.__public_time, get_absolute_time()) > rain_time_drop_ms)
    else if (SCALE_US_TO_MS(absolute_time_diff_us(Cube.__public_time, get_absolute_time())) > rain_time_drop_ms)
    {
        --z;
        if (z < 0)
            another_drop = 1;
        else
        {
            Cube.change_Z(Z_table[z]);
            Cube.__public_time = get_absolute_time();
        }
    }
    if (!another_drop)
        Cube.display();
    

}