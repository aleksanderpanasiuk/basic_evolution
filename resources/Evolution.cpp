#include "Evolution.h"
#include "Parameters.h"

Evolution::Evolution()
{

}

void Evolution::randomize_points()
{
    for (int i = 0; i < number_of_points; i++)
    {
        double x = ((rand() % 10000) / 1000.0);
        double y = ((rand() % 10000) / 1000.0) - 5;

        points.push_back({x, y});
    }
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
        parameters.calculate_fitness(number_of_points, points);
        parameters.fitness_sort();

        if (i%save_step == 0)
        {
            std::string file_path = "resources/generations/parameters_" +
                std::to_string(i) + ".csv";
            parameters.write_to_file(file_path);
        }
    }
}
