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

void heavy_rain(cube &Cube)
{

    static flag another_drop;
    uint rain_time_drop_ms = 75;
    const uint8_t drop_number = 10;

    static led Drops[drop_number];

    if (Cube.get_display_state() == DISPLAY_STATE_INIT)
    {
        another_drop = 0;

        Cube.clr_leds();
        for (int i = 0; i < drop_number; i++)
        {
            int8_t x = rand() % MAX_LEDS_X;
            int8_t y = rand() % MAX_LEDS_Y;
            int8_t z = rand() % MAX_LEDS_Z;
            Drops[i].__set(x, y, z);
            Cube.add_led(X_table[x], Y_table[y], Z_table[z]);
        }
        Cube.__public_time = get_absolute_time();
    }
    else if (SCALE_US_TO_MS(absolute_time_diff_us(Cube.__public_time, get_absolute_time())) > rain_time_drop_ms)
    {
        for (int i = 0; i < drop_number; i++)
        {
            --Drops[i].__z;
            if (Drops[i].__z < 0)
            {
                int8_t x = rand() % MAX_LEDS_X;
                int8_t y = rand() % MAX_LEDS_Y;
                Drops[i].__x = x;
                Drops[i].__y = y;
                Drops[i].__z = 4;
                Cube.emplace_led(i, X_table[x], Y_table[y], Z_table[Drops[i].__z]);
            }
            else
            {
                Cube.__leds[i].__off();
                Cube.__leds[i].__z = Z_table[Drops[i].__z];
            }
        }
        Cube.__public_time = get_absolute_time();
    }
    if (!another_drop)
        Cube.display();
}