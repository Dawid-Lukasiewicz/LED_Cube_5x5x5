#include "animations.hpp"

#include <cstdlib>
#include <ctime>

typedef uint8_t flag;

void random_led(cube &Cube)
{
    if (Cube.get_display_state() == 2)
    {
        Cube.clr_leds();
        Cube.reset_display_state();
    }
    if (Cube.get_display_state() == 0)
    {
        uint8_t x = std::rand()%5;
        uint8_t y = std::rand()%5;
        uint8_t z = std::rand()%5;

        Cube.add_led(X_table[x], Y_table[y], Z_table[z]);
    }
    Cube.display(500);
}

void rain(cube &Cube)
{

}