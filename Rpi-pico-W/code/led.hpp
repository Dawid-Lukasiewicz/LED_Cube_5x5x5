#ifndef LED
#define LED

#include "pico/stdlib.h"

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

class led
{
public:

    uint8_t __x;
    uint8_t __y;
    uint8_t __z;

    led() = delete;
    led(uint8_t x, uint8_t y, uint8_t z);
    ~led();

    void __set();
    void __clr();
};

#endif