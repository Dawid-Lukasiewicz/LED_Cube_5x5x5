#include "cube.hpp"
#include <stdio.h>

namespace task_handlers
{
    extern TaskHandle_t main_thread;
    extern TaskHandle_t wifi_thread;
}

cube::cube() {}

cube::cube(uint32_t size)
{
    __leds.reserve(size);
    pin_layouts["X0"] = 0;
    pin_layouts["X1"] = 1;
    pin_layouts["X2"] = 2;
    pin_layouts["X3"] = 3;
    pin_layouts["X4"] = 4;

    pin_layouts["Y0"] = 0;
    pin_layouts["Y1"] = 1;
    pin_layouts["Y2"] = 2;
    pin_layouts["Y3"] = 3;
    pin_layouts["Y4"] = 4;

    pin_layouts["Z0"] = 0;
    pin_layouts["Z1"] = 1;
    pin_layouts["Z2"] = 2;
    pin_layouts["Z3"] = 3;
    pin_layouts["Z4"] = 4;
}

cube::~cube() {}

void cube::add_led(const led & input_led)
{
    led new_led(input_led);
    __leds.push_back(new_led);
}

void cube::add_leds(std::vector<led> &leds)
{
    __leds.insert(__leds.begin(), leds.begin(), leds.end());
}

void cube::add_led(uint8_t x, uint8_t y, uint8_t z)
{
    led new_led(x, y, z);
    __leds.push_back(new_led);
}

void cube::emplace_led(uint8_t index, uint8_t x, uint8_t y, uint8_t z)
{
    if (index < __leds.size())
    {
        __leds[index].__off();
        __leds[index] = led(x, y, z);
    }
    if (xCubeQueueSend != NULL)
    {
        for (int i = 0; i < __leds.size(); i++)
        {
            xQueueSend(xCubeQueueSend, (const void*)&__leds[i], 0);
        }
    }
}

void cube::clr_leds()
{
    if (__leds.size() == 0)
        return;

    for (int i = 0; i < __leds.size(); i++)
    {
        __leds[i].__off();
    }
    __leds.clear();
}

void cube::display()
{
    if (__display_state == 0)
    {
        if (__leds.size() == 0)
            return;
        if (xCubeQueueSend != NULL && task_handlers::wifi_thread != NULL)
        {
            for (int i = 0; i < __leds.size(); i++)
            {
                xQueueSend(xCubeQueueSend, (const void*)&__leds[i], 0);
            }
            xTaskNotifyGive(task_handlers::wifi_thread);
        }
        __display_state = 1;
        __display_led_counter = 0;
        __display_led_time = SCALE_S_TO_US(1) / (__leds.size()*DISPLAY_FREQ);
    }
    if (__display_state == 1)
    {
        if (__display_led == 0)
        {
            __display_led = 1;
            __display_led_start = get_absolute_time();
        }
        if ( __display_led == 1
                && absolute_time_diff_us(__display_led_start, get_absolute_time()) <= __display_led_time )
            {
                __leds.at(__display_led_counter).__on();
            }
        else
        {
            __display_led = 0;
            __leds.at(__display_led_counter).__off();

            ++__display_led_counter;
            if (__display_led_counter >= __leds.size()) __display_led_counter = 0;
        }
    }
}

void cube::display(uint64_t display_time_ms)
{
    if (__display_state == 0)
    {
        if (xCubeQueueSend != NULL && task_handlers::wifi_thread != NULL)
        {
            for (int i = 0; i < __leds.size(); i++)
            {
                xQueueSend(xCubeQueueSend, (const void*)&__leds[i], 0);
            }
            xTaskNotifyGive(task_handlers::wifi_thread);
        }
        __display_state = 1;
        __display_led_counter = 0;
        __display_led_time = SCALE_S_TO_US(1) / (__leds.size()*DISPLAY_FREQ);
        __display_time = SCALE_MS_TO_US(display_time_ms);
        __display_start = get_absolute_time();

        /* To prevent from partial display assign value at which all leds turn on at least once*/
        if (__display_time < __display_led_time * __leds.size())
            __display_time = __display_led_time * __leds.size();
    }
    if (absolute_time_diff_us(__display_start, get_absolute_time()) <= __display_time)
    {
        if (__display_led == 0)
        {
            __display_led = 1;
            __display_led_start = get_absolute_time();
        }
        if ( __display_led == 1
            && absolute_time_diff_us(__display_led_start, get_absolute_time()) <= __display_led_time )
        {
            __leds.at(__display_led_counter).__on();
        }
        else
        {
            __display_led = 0;
            __leds.at(__display_led_counter).__off();

            ++__display_led_counter;
            if (__display_led_counter >= __leds.size()) __display_led_counter = 0;
        }
    }
    else
    {
        __leds.at(__display_led_counter).__off();
        __display_state = 2;
    }
}

void cube::change_X(uint8_t x)
{
    for (uint8_t i = 0; i < __leds.size(); i++)
    {
        __leds.at(i).__off();
        __leds.at(i).__x = x;
    }
}

void cube::change_Y(uint8_t y)
{
    for (uint8_t i = 0; i < __leds.size(); i++)
    {
        __leds.at(i).__off();
        __leds.at(i).__y = y;
    }
}

void cube::change_Z(uint8_t z)
{
    for (uint8_t i = 0; i < __leds.size(); i++)
    {
        __leds.at(i).__off();
        __leds.at(i).__z = z;
    }
}

flag cube::get_display_state()
{
    return __display_state;
}

void cube::reset_display_state()
{
    __display_state = 0;
}
