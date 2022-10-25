#ifndef PARAMETERS_H
#define PARAMETERS_H
#include<iostream>
#include<vector>

class Parameters
{
    public:
        const int POPULATION_SIZE = 200, NUMBER_OF_PARAMETERS = 10;
        std::vector<std::vector<double>> parameters;

        Parameters();
        void fill_random();
        void print_top_parameters(int, bool);
        double calculate_function(double, std::vector<double>);
        void write_to_file();
        void read_from_file();
        void calculate_fitness(int, std::pair<double, double>[]);
        void fitness_sort();
        static bool compare_fitness(double [], double []);
        void kill_bottom(int);
        void pairing(int);
        std::pair<std::vector<double>, std::vector<double>> mating(int, int);
};

#endif