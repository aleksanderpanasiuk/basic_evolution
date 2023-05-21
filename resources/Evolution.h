#ifndef EVOLUTION_H
#define EVOLUTION_H
#include "Points.h"
#include "Parameters.h"

class Evolution
{
    private:
        int creatures_to_kill;
        int number_of_points = 10;
        Points points = *new Points(number_of_points);
        Parameters parameters;

    public:
        Evolution();
        void randomize_points();
        void read_points();
        int get_number_of_points();
        void fill_random_parameters();
        void run_simulation(int number_of_generations, int save_step);
};

#endif
