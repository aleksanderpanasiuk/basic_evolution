#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "Parameters.h"
#include <fstream>


class Evolution
{
    private:
        int creatures_to_kill = 100;
        int number_of_points = 10;
        std::vector<std::pair<double, double>> points;
        Parameters parameters;

        std::string points_file_path = "resources/points.csv";
        std::string parameters_file_path = "resources/generations/parameters_";

    public:
        Evolution(int population_size, int number_of_parameters);
        void randomize_points();
        void fill_random_parameters();
        void run_simulation(int number_of_generations, int save_step);
};

#endif
