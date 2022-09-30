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
    if (__display_flag == 0)
    {
        __display_flag = 1;
        __display_start = get_absolute_time();
    }
    else if (__display_flag == 1 && get_absolute_time() - __display_start <= 100)
    {
        __leds.at(__display_counter).__on();
    }
    else
    {
        __display_flag = 0;
        __leds.at(__display_counter).__off();

        ++__display_counter;
        if (__display_counter >= size) __display_counter = 0;
    }
}
