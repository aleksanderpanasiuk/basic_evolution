#include "Evolution.h"

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

void Evolution::run_simulation()
{
    for (int i = 0; i <= number_of_generations; i++)
    {
        parameters.kill_bottom(creatures_to_kill);
        parameters.calculate_fitness(number_of_points, points.points);
        parameters.fitness_sort();

        if (i%save_step == 0)
        {
            parameters.write_to_file(file_path);
            parameters.print_top_parameters(3, true);
            std::cout << "\n";
        }
    }
}
