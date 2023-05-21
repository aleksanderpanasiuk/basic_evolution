#include <iostream>
#include "resources/Evolution.h"

int main()
{
    srand(time(0));

    Evolution evolution;
    evolution.randomize_points();
    evolution.read_points();
    evolution.fill_random_parameters();
    evolution.run_simulation(100, 10);

    return 0;
}
