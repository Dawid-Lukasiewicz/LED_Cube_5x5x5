#ifndef ANIMATIONS
#define ANIMATIONS

#include "cube.hpp"

void random_led(cube &Cube);
void rain(cube &Cube);
void heavy_rain(cube &Cube);
void expanding_cube(cube &Cube);
void expanding_star(cube &Cube);
void solid_cube(cube &Cube);
void benchmark_animiation(cube &Cube, uint8_t &select_flag, uint64_t measure_time);

void received_pattern(cube &Cube);

#endif
