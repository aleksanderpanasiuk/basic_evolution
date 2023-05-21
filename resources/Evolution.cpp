#include "Evolution.h"
#include "Points.h"
#include "Parameters.h"

Evolution::Evolution()
{
    creatures_to_kill = 100;
    number_of_points = 10;
}

void Evolution::randomize_points()
{
    points.randomize_points();
}

void Evolution::read_points()
{
    points.read_points();
}

int Evolution::get_number_of_points()
{
    return number_of_points;
}

void Evolution::fill_random_parameters()
{
    parameters.fill_random();
}

void Evolution::run_simulation(int number_of_generations, int save_step)
{
    for (int i = 0; i <= number_of_generations; i++)
    {
        parameters.kill_bottom(creatures_to_kill);
        parameters.calculate_fitness(number_of_points, points.points);
        parameters.fitness_sort();

        if (i%save_step == 0)
        {
            std::string file_path = "resources/generations/parameters_" +
                std::to_string(i) + ".csv";
            parameters.write_to_file(file_path);
        }
    }
}
