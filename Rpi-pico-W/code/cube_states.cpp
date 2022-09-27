#include "cube_states.hpp"


cube_states::cube_states(/* args */)
{
}

cube_states::~cube_states()
{
}


void cube_states::set_LED(coordX x)
{
    uint32_t mask = 1ul << x;
    gpio_clr_mask(mask);
}


void cube_states::clr_LED(coordX x)
{
    uint32_t mask = 1ul << x;
    gpio_set_mask(mask);
}


void cube_states::set_LED(coordY y)
{
    uint32_t mask = 1ul << y;
    gpio_clr_mask(mask);
}


void cube_states::clr_LED(coordY y)
{
    uint32_t mask = 1ul << y;
    gpio_set_mask(mask);
}


void cube_states::set_LED(coordZ z)
{
    uint32_t mask = 1ul << z;
    gpio_set_mask(mask);
}


void cube_states::clr_LED(coordZ z)
{
    uint32_t mask = 1ul << z;
    gpio__mask(mask);
}