#include "numbers.hpp"
#include "led.hpp"

extern const uint8_t x;
extern const uint8_t Y_table[5];
extern const uint8_t Z_table[5];

void zero(cube &Cube, uint8_t x)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y1, Z1);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y1, Z3);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y2, Z4);
    }

    Cube.display();
}

void one(cube &Cube, uint8_t x)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y3, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y2, Z3);
        Cube.add_led(x, Y1, Z3);
    }

    Cube.display();
}

void two(cube &Cube, uint8_t x)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y1, Z0);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y3, Z0);
        Cube.add_led(x, Y1, Z1);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y1, Z3);
    }

    Cube.display();
}

void three(cube &Cube, uint8_t x)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y3, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y1, Z0);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y1, Z4);
        Cube.add_led(x, Y2, Z4);
    }

    Cube.display();
}

void four(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y3, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y2, Z3);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y3, Z4);
    }
    
    Cube.display();
}

void five(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y1, Z0);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y1, Z3);
        Cube.add_led(x, Y1, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y3, Z4);
    }

    Cube.display();
}

void six(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y1, Z3);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y1, Z1);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y2, Z2);
    }
    Cube.display();
}

void seven(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y2, Z1);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y1, Z4);
    }

    Cube.display();
}

void eight(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y1, Z0);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y3, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y1, Z1);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y3, Z3);
        Cube.add_led(x, Y1, Z3);
        Cube.add_led(x, Y1, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y3, Z4);
    }

    Cube.display();
}

void nine(cube &Cube, uint8_t x)
{
    if (Cube.get_display_state() == 0)
    {
        Cube.add_led(x, Y1, Z0);
        Cube.add_led(x, Y2, Z0);
        Cube.add_led(x, Y3, Z1);
        Cube.add_led(x, Y3, Z2);
        Cube.add_led(x, Y2, Z2);
        Cube.add_led(x, Y1, Z2);
        Cube.add_led(x, Y1, Z3);
        Cube.add_led(x, Y1, Z4);
        Cube.add_led(x, Y2, Z4);
        Cube.add_led(x, Y3, Z4);
        Cube.add_led(x, Y3, Z3);
    }
    
    Cube.display();
}
