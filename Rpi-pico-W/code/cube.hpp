#ifndef CUBE
#define CUBE

#include <vector>
// #include <memory>

#include "pico/stdlib.h"

#include "led.hpp"

class cube
{
private:
    std::vector<led*> __leds;

public:

    cube(/* args */);
    ~cube();

    void add_led(led *led);
    void add_led(std::vector<led> *leds);

    void display();

};

#endif