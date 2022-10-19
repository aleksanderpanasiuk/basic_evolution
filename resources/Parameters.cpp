#include "Parameters.h"
#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

Parameters::Parameters()
{
    vector<double> v;

    for (int i = 0; i <= NUMBER_OF_PARAMETERS; i++)
    {
        v.push_back(0);
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        parameters.push_back(v);
    }
}

void Parameters::fill_random()
{
    srand(time(0));

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            double random_number = ((rand() % 200000) / 1000.0) - 100;
            parameters[i][j] = random_number;
        }

        parameters[i][10] = 0;
    }
}

void Parameters::print_top_parameters(int n=10, bool only_fitness=false)
{
    for (int i = 0; i < min(n, POPULATION_SIZE); i++)
    {
        cout << i << ": ";

        if (!only_fitness)
        {
            for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
            {
                cout << parameters[i][j] << " | ";
            }
        }

        cout << "fitness: " << parameters[i][10] << "\n";
    }
}

double Parameters::calculate_function(double x, vector<double> par)
{
    const double PI = 3.1415;
    double y = par[0] * sin((par[1]*x + par[2])*PI/180);
    y += par[3] * sin((par[4]*x + par[5])*PI/180);
    y += par[6] * sin((par[7]*x + par[8])*PI/180);
    y += par[9];

    return y;
}

void Parameters::calculate_fitness(int no_points, std::pair<double, double> points[])
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < no_points; j++)
        {
            double x = points[i].first;
            double y = calculate_function(x, parameters[i]);
            double points_y = points[i].second;

            parameters[i][NUMBER_OF_PARAMETERS] += (points_y - y) * (points_y - y);
        }

        parameters[i][NUMBER_OF_PARAMETERS] /= no_points;
    }
}

void Parameters::fitness_sort()
{
    sort(parameters.begin(), parameters.end(), 
    [] (const std::vector<double> &a, const std::vector<double> &b)
    {
        return a[10] < b[10];
    });
}

void Parameters::write_to_file()
{
    ofstream output_file("resources/parameters.txt");

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            output_file << parameters[i][j] << ' ';
        }

        output_file << parameters[i][NUMBER_OF_PARAMETERS] << "\n";
    }

    output_file.close();
}


void Parameters::read_from_file()
{
    ifstream input_file("resources/parameters.txt");

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
        {
            input_file >> parameters[i][j];
        }
    }

    input_file.close();
}
