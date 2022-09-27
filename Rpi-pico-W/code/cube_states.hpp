#include "pico/stdlib.h"

typedef uint coordX;
typedef uint coordY;
typedef uint coordZ;

class cube_states
{
public:

    cube_states(/* args */);
    ~cube_states();

    void set_LED(coordX x);

    void clr_LED(coordX x);

    void set_LED(coordY y);

    void clr_LED(coordY y);

    void set_LED(coordZ z);

    void clr_LED(coordZ z);
};