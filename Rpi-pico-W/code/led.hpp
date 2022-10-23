#ifndef LED
#define LED

#include "pico/stdlib.h"

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