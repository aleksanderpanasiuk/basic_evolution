#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>

class Parameters
{
    private:
        int population_size;
        int number_of_parameters;

        std::vector<std::vector<double>> parameters;
        void pairing(int creatures_to_kill);

    public:
        Parameters(int population_size, int number_of_parameters);

        void fill_random();
        void print_top_parameters(int n, bool only_fitness);
        double calculate_function(double x, std::vector<double> par);
        void write_to_file(std::string file_path);
        void read_from_file(std::string file_path);
        void calculate_fitness(std::vector<std::pair<double, double>>& points);
        void fitness_sort();
        void kill_bottom(int n);
        std::pair<std::vector<double>, std::vector<double>> mating(int a, int b);
        double mutation_result();
};

#endif
