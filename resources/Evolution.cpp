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

    std::ofstream output_file(points_file_path);

    output_file << "x,y\n";

    for (std::pair<double, double>& p : points)
    {
        output_file << p.first << ", " << p.second << "\n";
    }

    output_file.close();
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
            parameters.write_to_file(
                parameters_file_path + std::to_string(i) + ".csv");
        }
    }
}
