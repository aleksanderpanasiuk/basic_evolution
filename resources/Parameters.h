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
};

#endif