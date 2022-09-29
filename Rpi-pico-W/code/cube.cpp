#include "cube.hpp"


cube::cube() {}

cube::cube(uint32_t size)
{
    __leds.reserve(size);
}

cube::~cube() {}

// Not sure if this should be here
void cube::add_led(led *led)
{
    __leds.push_back(*led);
}

void cube::add_led(led &led)
{
    __leds.push_back(led);
}

void cube::add_led(std::vector<led> &leds)
{
    __leds.insert(__leds.begin(), leds.begin(), leds.end());
}

void cube::add_leds(uint8_t x, uint8_t y, uint8_t z)
{
    led new_led(x, y, z);
    __leds.push_back(new_led);
}

void cube::display()
{
    int size = __leds.size();
    for (uint8_t i = 0; i < size; i++)
    {
        __leds.at(i).__on();
        sleep_ms(50);
        __leds.at(i).__off();
    }
    
}
