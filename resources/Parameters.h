#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <iostream>
#include <vector>

class Parameters
{
    private:
        const int POPULATION_SIZE = 200, NUMBER_OF_PARAMETERS = 10;
        std::vector<double> v = *new std::vector<double>(NUMBER_OF_PARAMETERS+1, 0);
        std::vector<std::vector<double>> parameters = *new std::vector<std::vector<double>>(POPULATION_SIZE, v);
    public:
        void fill_random();
        void print_top_parameters(int n, bool only_fitness);
        double calculate_function(double x, std::vector<double> par);
        void write_to_file(std::string file_path);
        void read_from_file(std::string file_path);
        void calculate_fitness(int no_points, std::pair<double, double> points[]);
        void fitness_sort();
        void kill_bottom(int n);
        void pairing(int n);
        std::pair<std::vector<double>, std::vector<double>> mating(int a, int b);
        double mutation_result();
};

#endif