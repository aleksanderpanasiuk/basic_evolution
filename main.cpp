#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include "resources/Points.h"
#include "resources/Parameters.h"

using namespace std;

int main()
{
    int creatures_to_kill = 100;
    int number_of_generations = 10000;
    Points points;
    points.read_points();

    Parameters parameters;
    parameters.fill_random();
    parameters.write_to_file();
    parameters.read_from_file();

    for (int i = 0; i < number_of_generations; i++)
    {
        // cout << i << " gen: \n";
        // parameters.print_top_parameters(3, true);

        parameters.kill_bottom(creatures_to_kill);
        parameters.pairing(creatures_to_kill);
        parameters.calculate_fitness(points.NUMBER_OF_POINTS, points.points);
        parameters.fitness_sort();
    }

    cout << number_of_generations << " gen: \n";
    parameters.print_top_parameters(3, true);

    return 0;
}