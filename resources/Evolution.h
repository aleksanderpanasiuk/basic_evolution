#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "Points.h"
#include "Parameters.h"

class Evolution
{
    private:
        int creatures_to_kill = 100;
        int number_of_generations = 100;
        int number_of_points = 10;
        Points points(number_of_points);
        Parameters parameters;

    public:
        void randomize_points();
        void read_points();
        int get_number_of_points();
        void fill_random_parameters();
        void run_simulation();
};

#endif
