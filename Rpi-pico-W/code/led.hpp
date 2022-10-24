#ifndef LED
#define LED

#include "pico/stdlib.h"

class led
{
public:

    int __x;
    int __y;
    int __z;

    led();
    led(int x, int y, int z);
    ~led();

    void __set(int x, int y, int z);
    void __on();
    void __off();
};

#endif