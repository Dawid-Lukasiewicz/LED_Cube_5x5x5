#include "led.hpp"

led::led() {}

led::led(int8_t x, int8_t y, int8_t z)
: __x(x), __y(y), __z(z)
{}

led::~led() {}

void led::__set(int8_t x, int8_t y, int8_t z)
{
    __x = x;
    __y = y;
    __z = z;
}

void led::__on()
{
    uint32_t mask = 1ul <<__x;
    gpio_clr_mask(mask);
    mask = 1ul <<__y;
    gpio_clr_mask(mask);
    mask = 1ul <<__z;
    gpio_set_mask(mask);
}

void led::__off()
{
    uint32_t mask = 1ul <<__x;
    gpio_set_mask(mask);
    mask = 1ul <<__y;
    gpio_set_mask(mask);
    mask = 1ul <<__z;
    gpio_clr_mask(mask);
}