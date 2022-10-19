#ifndef PARAMETERS_H
#define PARAMETERS_H
#include<iostream>

class Parameters
{
    public:
        const int POPULATION_SIZE = 200, NUMBER_OF_PARAMETERS = 10;
        double parameters[200][11];

        void fill_random();
        void print_top_parameters(int);
        void calculate_function(double, double []);
        void write_to_file();
        void read_from_file();
};

#endif