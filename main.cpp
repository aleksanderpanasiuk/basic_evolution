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
    int number_of_generations = 1000;
    Points points(10);
    points.randomize_points();
    points.read_points();

    Parameters parameters;
    parameters.fill_random();

    for (int i = 0; i <= number_of_generations; i++)
    {
        parameters.kill_bottom(creatures_to_kill);
        parameters.calculate_fitness(points.get_number_of_points(), points.points);
        parameters.fitness_sort();
        if (i%100 == 0)
        {
            std::string file_path = "resources/generations/parameters_" +
                std::to_string(i) + ".csv";
            parameters.write_to_file(file_path);
            parameters.print_top_parameters(3, true);
        }
    }
    parameters.write_to_file("resources/parameters.csv");

    return 0;
}
