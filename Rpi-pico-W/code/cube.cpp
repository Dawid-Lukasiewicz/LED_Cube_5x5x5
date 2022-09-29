#include "cube.hpp"


cube::cube(/* args */)
{}

cube::~cube()
{}

void cube::add_led(led *led)
{
    __leds.push_back(led);
}

void cube::add_led(std::vector<led*> leds)
{
    __leds.insert(__leds.begin(), leds.begin(), leds.end());
}

void cube::display()
{
    size = __leds.size();
    for (uint8_t i = 0; i < size; i++)
    {
        __leds.at(i)->__set();
        sleep_ms(50);
        __leds.at(i)->__clr();
    }
    
}
