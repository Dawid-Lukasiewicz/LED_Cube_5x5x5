#ifndef CUBE
#define CUBE

#include <vector>
// #include <memory>

#include "pico/stdlib.h"

#include "led.hpp"

typedef uint8_t flag;

#define DISPLAY_FREQ 60
#define SCALE_S_TO_US 1000000
#define SCALE_MS_TO_US 1000

class cube
{
private:
    std::vector<led> __leds;
    absolute_time_t __display_start;
    absolute_time_t __display_led_start;
    
    uint64_t __display_led_time = 0;
    uint64_t __display_time = 0;
    flag __display_state = 0;
    flag __display_led = 0;
    uint8_t __display_led_counter = 0;

public:

    cube(/* args */);
    cube(uint32_t size);
    ~cube();
    
    // Not sure if this one should be 
    void add_leds(led *led);
    void add_leds(led &led);
    void add_leds(std::vector<led> &leds);
    void add_led(uint8_t x, uint8_t y, uint8_t z);

    void clr_leds();
    /* Inefficient way to find and clear led by its coords*/
    void clr_leds(uint8_t x, uint8_t y, uint8_t z);

    // TO FIX
    void display();
    void display(uint64_t display_time_ms);

    void change_X(uint8_t x);
    void change_Y(uint8_t y);
    void change_Z(uint8_t z);

    flag get_display_state();
    void reset_display_state();
};

#endif