#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "resources/Points.h"
#include "resources/Parameters.h"

int main()
{
    int creatures_to_kill = 100;
    int number_of_generations = 10;
    Points points(10);
    points.randomize_points();
    points.read_points();

    Parameters parameters;
    parameters.fill_random();
    parameters.write_to_file();
    parameters.read_from_file();

    std::cout << points;

    for (int i = 0; i < number_of_generations; i++)
    {
        // std::cout << i << " gen: \n";
        // parameters.print_top_parameters(3, true);

        parameters.kill_bottom(creatures_to_kill);
        parameters.pairing(creatures_to_kill);
        parameters.calculate_fitness(points.get_number_of_points(), points.points);
        parameters.fitness_sort();
    }

    std::cout << number_of_generations << " gen: \n";
    parameters.print_top_parameters(3, true);
    parameters.write_to_file();

    return 0;
}
