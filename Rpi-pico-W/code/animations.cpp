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
    Cube.display(1000);
}

void rain(cube &Cube)
{
    static int8_t x;
    static int8_t y;
    static int8_t z;
    static flag another_drop;
    uint rain_time_drop_ms = 100;
    if (Cube.get_display_state() == DISPLAY_STATE_INIT 
        || another_drop)
    {
        z = 4;
        another_drop = 0;

        x = std::rand() % MAX_LEDS_X;
        y = std::rand() % MAX_LEDS_Y;

        Cube.clr_leds();
        Cube.reset_display_state();
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
            Cube.clr_leds();
            Cube.reset_display_state();
            Cube.add_led(X_table[x], Y_table[y], Z_table[z]);
            Cube.__public_time = get_absolute_time();
        }
    }
    if (!another_drop)
        Cube.display();
}

void heavy_rain(cube &Cube)
{

    static flag another_drop;
    uint rain_time_drop_ms = 125;
    const uint8_t drop_number = 8;

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
        Cube.clr_leds();
        Cube.reset_display_state();
        for (int i = 0; i < drop_number; i++)
        {
            --Drops[i].__z;
            if (Drops[i].__z < 0)
            {
                Drops[i].__x = rand() % MAX_LEDS_X;
                Drops[i].__y = rand() % MAX_LEDS_Y;
                Drops[i].__z = 4;
            }
            Cube.add_led(X_table[Drops[i].__x],
                        Y_table[Drops[i].__y],
                        Z_table[Drops[i].__z]);
        }
        Cube.__public_time = get_absolute_time();
    }
    if (!another_drop)
        Cube.display();
}

void expanding_cube(cube &Cube)
{
    int expand_time_ms = 350;
    static int cube_size;
    static flag expanding;
    static flag direction;
    if (Cube.get_display_state() == DISPLAY_STATE_INIT)
    {
        cube_size = 0;
        expanding = 1;
        direction = 0;
        Cube.__public_time = get_absolute_time();
    }
    if (SCALE_US_TO_MS(absolute_time_diff_us(Cube.__public_time, get_absolute_time())) > expand_time_ms)
    {
        if (direction)
            --cube_size;
        else
            ++cube_size;

        if (cube_size >= 2 || cube_size <= 0)
            direction ^= 1;  

        expanding = 1;
        Cube.clr_leds();
        Cube.reset_display_state();
        Cube.__public_time = get_absolute_time();
    }

    switch (cube_size)
    {
    case 0:
        if (expanding)
        {
            expanding = 0;
            Cube.add_led(X2, Y2, Z2);
        }
        break;

    case 1:
        if (expanding)
        {
            expanding = 0;
            Cube.add_led(X1, Y1, Z1);
            Cube.add_led(X1, Y2, Z1);
            Cube.add_led(X1, Y3, Z1);

            Cube.add_led(X3, Y1, Z1);
            Cube.add_led(X3, Y2, Z1);
            Cube.add_led(X3, Y3, Z1);

            Cube.add_led(X2, Y1, Z1);
            Cube.add_led(X2, Y3, Z1);

            Cube.add_led(X1, Y1, Z3);
            Cube.add_led(X1, Y2, Z3);
            Cube.add_led(X1, Y3, Z3);

            Cube.add_led(X3, Y1, Z3);
            Cube.add_led(X3, Y2, Z3);
            Cube.add_led(X3, Y3, Z3);

            Cube.add_led(X2, Y1, Z3);
            Cube.add_led(X2, Y3, Z3);

            Cube.add_led(X3, Y1, Z2);
            Cube.add_led(X3, Y3, Z2);
            Cube.add_led(X1, Y1, Z2);
            Cube.add_led(X1, Y3, Z2);
        }
        break;

    case 2:
        if (expanding)
        {
            expanding = 0;
            Cube.add_led(X0, Y0, Z0);
            Cube.add_led(X0, Y1, Z0);
            Cube.add_led(X0, Y2, Z0);
            Cube.add_led(X0, Y3, Z0);
            Cube.add_led(X0, Y4, Z0);

            Cube.add_led(X4, Y0, Z0);
            Cube.add_led(X4, Y1, Z0);
            Cube.add_led(X4, Y2, Z0);
            Cube.add_led(X4, Y3, Z0);
            Cube.add_led(X4, Y4, Z0);

            Cube.add_led(X1, Y0, Z0);
            Cube.add_led(X2, Y0, Z0);
            Cube.add_led(X3, Y0, Z0);

            Cube.add_led(X1, Y4, Z0);
            Cube.add_led(X2, Y4, Z0);
            Cube.add_led(X3, Y4, Z0);

            Cube.add_led(X0, Y0, Z4);
            Cube.add_led(X0, Y1, Z4);
            Cube.add_led(X0, Y2, Z4);
            Cube.add_led(X0, Y3, Z4);
            Cube.add_led(X0, Y4, Z4);

            Cube.add_led(X4, Y0, Z4);
            Cube.add_led(X4, Y1, Z4);
            Cube.add_led(X4, Y2, Z4);
            Cube.add_led(X4, Y3, Z4);
            Cube.add_led(X4, Y4, Z4);

            Cube.add_led(X1, Y0, Z4);
            Cube.add_led(X2, Y0, Z4);
            Cube.add_led(X3, Y0, Z4);

            Cube.add_led(X1, Y4, Z4);
            Cube.add_led(X2, Y4, Z4);
            Cube.add_led(X3, Y4, Z4);

            Cube.add_led(X0, Y0, Z3);
            Cube.add_led(X0, Y0, Z2);
            Cube.add_led(X0, Y0, Z1);

            Cube.add_led(X4, Y0, Z3);
            Cube.add_led(X4, Y0, Z2);
            Cube.add_led(X4, Y0, Z1);

            Cube.add_led(X4, Y4, Z3);
            Cube.add_led(X4, Y4, Z2);
            Cube.add_led(X4, Y4, Z1);

            Cube.add_led(X0, Y4, Z3);
            Cube.add_led(X0, Y4, Z2);
            Cube.add_led(X0, Y4, Z1);
        }
        break;
    
    default:
        break;
    }

    Cube.display();

}

void expanding_star(cube &Cube)
{
    int expand_time_ms = 250;
    static int star_size;
    static flag change;
    static flag growing;
    if (Cube.get_display_state() == DISPLAY_STATE_INIT)
    {
        star_size = 0;
        change = 1;
        Cube.__public_time = get_absolute_time();
    }
    if (SCALE_US_TO_MS(absolute_time_diff_us(Cube.__public_time, get_absolute_time())) > expand_time_ms)
    {
        change = 1;
    }

    switch (star_size)
    {
    case 0:
        if (change)
        {
            change = 0;
            star_size++;

            Cube.clr_leds();
            Cube.reset_display_state();

            Cube.add_led(X2, Y2, Z2);

            Cube.__public_time = get_absolute_time();
        }
        break;
    case 1:
        if (change)
        {
            change = 0;
            star_size++;
            // Cube.clr_leds();
            Cube.reset_display_state();

            Cube.add_led(X3, Y3, Z3);
            Cube.add_led(X3, Y3, Z1);

            Cube.add_led(X3, Y1, Z3);
            Cube.add_led(X3, Y1, Z1);
            
            Cube.add_led(X1, Y3, Z3);
            Cube.add_led(X1, Y3, Z1);

            Cube.add_led(X1, Y1, Z3);
            Cube.add_led(X1, Y1, Z1);

            Cube.__public_time = get_absolute_time();
        }
        break;

    case 2:
        if (change)
        {
            change = 0;
            star_size++;
            // Cube.clr_leds();
            Cube.reset_display_state();

            Cube.add_led(X4, Y4, Z4);
            Cube.add_led(X4, Y4, Z0);

            Cube.add_led(X4, Y0, Z4);
            Cube.add_led(X4, Y0, Z0);
            
            Cube.add_led(X0, Y4, Z4);
            Cube.add_led(X0, Y4, Z0);

            Cube.add_led(X0, Y0, Z4);
            Cube.add_led(X0, Y0, Z0);

            Cube.__public_time = get_absolute_time();
        }
        break;

    case 3:
        if (change)
        {
            change = 0;
            star_size++;
            Cube.clr_leds();
            Cube.reset_display_state();

            Cube.add_led(X3, Y3, Z3);
            Cube.add_led(X3, Y3, Z1);

            Cube.add_led(X3, Y1, Z3);
            Cube.add_led(X3, Y1, Z1);
            
            Cube.add_led(X1, Y3, Z3);
            Cube.add_led(X1, Y3, Z1);

            Cube.add_led(X1, Y1, Z3);
            Cube.add_led(X1, Y1, Z1);

            Cube.add_led(X4, Y4, Z4);
            Cube.add_led(X4, Y4, Z0);

            Cube.add_led(X4, Y0, Z4);
            Cube.add_led(X4, Y0, Z0);
            
            Cube.add_led(X0, Y4, Z4);
            Cube.add_led(X0, Y4, Z0);

            Cube.add_led(X0, Y0, Z4);
            Cube.add_led(X0, Y0, Z0);

            Cube.__public_time = get_absolute_time();
        }
        break;

    case 4:
        if (change)
        {
            change = 0;
            star_size = 0;
            Cube.clr_leds();
            Cube.reset_display_state();

            Cube.add_led(X4, Y4, Z4);
            Cube.add_led(X4, Y4, Z0);

            Cube.add_led(X4, Y0, Z4);
            Cube.add_led(X4, Y0, Z0);
            
            Cube.add_led(X0, Y4, Z4);
            Cube.add_led(X0, Y4, Z0);

            Cube.add_led(X0, Y0, Z4);
            Cube.add_led(X0, Y0, Z0);

            Cube.__public_time = get_absolute_time();
        }
        break;
    
    default:
        break;
    }
    Cube.display();
}

void received_pattern(cube &Cube)
{
    static flag active;
    led received_led;
    if (Cube.xCubeQueueReceive == NULL)
    {
        printf("Queue is not initialized at receiving data");
        return;
    }
    while (uxQueueMessagesWaiting(Cube.xCubeQueueReceive))
    {
        if (!active)
        {
            Cube.reset_display_state();
            Cube.clr_leds();
        }

        xQueueReceive(Cube.xCubeQueueReceive, &received_led, portMAX_DELAY);
        Cube.add_led(received_led);
        active = 1;
    }
    Cube.display();
    active = 0;
}