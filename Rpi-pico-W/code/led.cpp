#include "led.hpp"

led::led(uint8_t x, uint8_t y, uint8_t z)
: __x(x), __y(y), __z(z)
{}

void led::__set()
{
    uint32_t mask;
    gpio_clr_mask((mask=1ul<<__x));
    gpio_clr_mask((mask=1ul<<__y));
    gpio_set_mask((mask=1ul<<__z));
}

void led::__clr()
{
    uint32_t mask;
    gpio_set_mask((mask=1ul<<__x));
    gpio_set_mask((mask=1ul<<__y));
    gpio_clr_mask((mask=1ul<<__z));
}