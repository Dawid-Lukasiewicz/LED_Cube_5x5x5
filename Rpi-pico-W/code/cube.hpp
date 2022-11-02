#ifndef CUBE
#define CUBE

#include <vector>
// #include <memory>

#include "pico/stdlib.h"

#include "led.hpp"

typedef uint8_t flag;

#define MAX_LEDS_X 5
#define MAX_LEDS_Y 5
#define MAX_LEDS_Z 5

#define X0 15U
#define X1 13U
#define X2 12U
#define X3 11U
#define X4 10U

#define Y0 14U
#define Y1 16U
#define Y2 17U
#define Y3 18U
#define Y4 19U

#define Z0 27U
#define Z1 26U
#define Z2 22U
#define Z3 21U
#define Z4 20U

const uint8_t X_table[5] = {X0, X1, X2, X3, X4};
const uint8_t Y_table[5] = {Y0, Y1, Y2, Y3, Y4};
const uint8_t Z_table[5] = {Z0, Z1, Z2, Z3, Z4};

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
    flag __pattern_change = 0;

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