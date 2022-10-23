#ifndef LED
#define LED

#include "pico/stdlib.h"

class led
{
public:

    int8_t __x;
    int8_t __y;
    int8_t __z;

    led();
    led(int8_t x, int8_t y, int8_t z);
    ~led();

    void __set(int8_t x, int8_t y, int8_t z);
    void __on();
    void __off();
};

#endif