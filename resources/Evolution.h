#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "Parameters.h"

class Evolution
{
    private:
        int creatures_to_kill = 100;
        int number_of_points = 10;
        std::vector<std::pair<double, double>> points;
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
