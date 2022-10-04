#include "numbers.hpp"
#include "led.hpp"

extern const uint8_t X_table[5];
extern const uint8_t Y_table[5];
extern const uint8_t Z_table[5];

void zero(cube &Cube, uint64_t time_ms)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(X2, Y2, Z0);
        Cube.add_led(X2, Y1, Z1);
        Cube.add_led(X2, Y3, Z1);
        Cube.add_led(X2, Y1, Z2);
        Cube.add_led(X2, Y3, Z2);
        Cube.add_led(X2, Y1, Z3);
        Cube.add_led(X2, Y3, Z3);
        Cube.add_led(X2, Y2, Z4);
    }
    Cube.display(time_ms);
    if(Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
    }
}

void one(cube &Cube, uint64_t time_ms)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(X2, Y3, Z0);
        Cube.add_led(X2, Y3, Z1);
        Cube.add_led(X2, Y3, Z2);
        Cube.add_led(X2, Y3, Z3);
        Cube.add_led(X2, Y3, Z4);
        Cube.add_led(X2, Y2, Z3);
        Cube.add_led(X2, Y1, Z2);
    }
    Cube.display(time_ms);
    if(Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
    }
}

void two(cube &Cube, uint64_t time_ms)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(X2, Y1, Z0);
        Cube.add_led(X2, Y2, Z0);
        Cube.add_led(X2, Y3, Z0);
        Cube.add_led(X2, Y1, Z1);
        Cube.add_led(X2, Y2, Z2);
        Cube.add_led(X2, Y3, Z3);
        Cube.add_led(X2, Y2, Z4);
        Cube.add_led(X2, Y1, Z3);
    }
    Cube.display(time_ms);
    if(Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
    }
}

void three(cube &Cube, uint64_t time_ms)
{
    if(Cube.get_display_state() == 0)
    {
        Cube.add_led(X2, Y3, Z0);
        Cube.add_led(X2, Y3, Z1);
        Cube.add_led(X2, Y3, Z2);
        Cube.add_led(X2, Y3, Z3);
        Cube.add_led(X2, Y3, Z4);
        Cube.add_led(X2, Y1, Z0);
        Cube.add_led(X2, Y2, Z0);
        Cube.add_led(X2, Y1, Z2);
        Cube.add_led(X2, Y2, Z2);
        Cube.add_led(X2, Y1, Z4);
        Cube.add_led(X2, Y2, Z4);
    }
    Cube.display(time_ms);
    if(Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
    }
}

void four(cube &Cube, uint64_t time_ms)
{

}

void five(cube &Cube, uint64_t time_ms)
{

}

void six(cube &Cube, uint64_t time_ms)
{

}

void seven(cube &Cube, uint64_t time_ms)
{

}

void eight(cube &Cube, uint64_t time_ms)
{

}

void nine(cube &Cube, uint64_t time_ms)
{

}
