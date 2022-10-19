#include "Parameters.h"
#include<iostream>

using namespace std;

void Parameters::fill_random()
{
    srand(time(0));

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            double random_number = ((rand() % 20000) / 100.0) - 100;
            parameters[i][j] = random_number;
        }

        parameters[i][10] = 0;
    }
}

void Parameters::print_top_parameters(int n=10)
{
    for (int i = 0; i < min(n, POPULATION_SIZE); i++)
    {
        cout << i << ": ";

        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            cout << parameters[i][j] << " | ";
        }

        cout << "fitness: " << parameters[i][10] << "\n";
    }
}