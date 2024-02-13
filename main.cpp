#include <iostream>
#include "resources/Evolution.h"

int main()
{
    srand(time(0));

    Evolution evolution(200, 10);
    evolution.randomize_points();
    evolution.fill_random_parameters();
    evolution.run_simulation(100, 10);

    return 0;
}
