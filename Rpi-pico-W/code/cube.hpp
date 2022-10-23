#ifndef CUBE
#define CUBE

#include <vector>
// #include <memory>

#include "pico/stdlib.h"

#include "led.hpp"

typedef uint8_t flag;

#define DISPLAY_FREQ 60
#define SCALE_S_TO_US(s_time)       ((s_time)*1000000)
#define SCALE_MS_TO_US(ms_time)     ((ms_time)*1000)
#define SCALE_US_TO_MS(us_time)     ((us_time)/1000)

#define DISPLAY_STATE_INIT 0
#define DISPLAY_STATE_RUN 1
#define DISPLAY_STATE_FINISH 2

class cube
{
private:
    absolute_time_t __display_start;
    absolute_time_t __display_led_start;
    
    uint64_t __display_led_time = 0;
    uint64_t __display_time = 0;
    flag __display_state = 0;
    flag __display_led = 0;
    uint8_t __display_led_counter = 0;

public:
    std::vector<led> __leds;
    absolute_time_t __public_time;

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
    void clr_led(uint8_t x, uint8_t y, uint8_t z);

    void emplace_led(uint8_t index, uint8_t x, uint8_t y, uint8_t z);

    void display();
    void display(uint64_t display_time_ms);

    void change_X(uint8_t x);
    void change_Y(uint8_t y);
    void change_Z(uint8_t z);

    led& change_led(uint8_t index);

    flag get_display_state();
    void reset_display_state();
};

#endif