#ifndef CUBE
#define CUBE

#include <vector>
// #include <memory>

#include "pico/stdlib.h"

#include "led.hpp"

class cube
{
private:
    std::vector<led> __leds;
    absolute_time_t __display_start = 0;
    uint8_t __display_counter = 0;
    uint8_t __display_flag = 0;

public:

    cube(/* args */);
    cube(uint32_t size);
    ~cube();
    
    // Not sure if this one should be 
    void add_led(led *led);
    void add_led(led &led);
    void add_led(std::vector<led> &leds);
    void add_leds(uint8_t x, uint8_t y, uint8_t z);

    void display();

};

#endif