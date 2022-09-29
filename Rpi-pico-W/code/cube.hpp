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
    // uint8_t __size;
    // led *__leds;

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