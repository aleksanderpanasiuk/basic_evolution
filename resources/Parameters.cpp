#include "Parameters.h"
#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<vector>

Parameters::Parameters()
{
    std::vector<double> v;

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
    for (int i = 0; i < std::min(n, POPULATION_SIZE); i++)
    {
        std::cout << i << ": ";

        if (!only_fitness)
        {
            for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
            {
                std::cout << parameters[i][j] << " | ";
            }
        }

        std::cout << "fitness: " << parameters[i][10] << "\n";
    }
}

double Parameters::calculate_function(double x, std::vector<double> par)
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
    std::ofstream output_file("resources/parameters.txt");

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
    std::ifstream input_file("resources/parameters.txt");

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
        {
            input_file >> parameters[i][j];
        }
    }

    input_file.close();
}

void Parameters::kill_bottom(int n)
{
    for (int i = POPULATION_SIZE-n; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
            parameters[i][j] = 0;
    }

    pairing(n);
}

void Parameters::pairing(int n)
{
    std::vector<int> population;
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < POPULATION_SIZE-n; i++)
        population.push_back(i);

    random_shuffle(population.begin(), population.end());

    for (int i = 0; i < POPULATION_SIZE-n; i+= 2)
    {
        pairs.push_back(std::make_pair(population[i], population[i+1]));
    }

    for (int i = 0; i < (POPULATION_SIZE-n)/2; i++)
    {
        std::pair<std::vector<double>, std::vector<double>> p = mating(pairs[i].first, pairs[i].second);

        parameters[n + (i*2)] = p.first;
        parameters[n + (i*2)+1] = p.second;
    }
}

std::pair<std::vector<double>, std::vector<double>> Parameters::mating(int a, int b)
{
    std::vector<double> c;
    std::vector<double> d;
    std::vector<int> dom_genes;
    srand(time(0));

    for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
    {
        c.push_back(NULL);
        d.push_back(NULL);
        dom_genes.push_back(i);
    }

    random_shuffle(dom_genes.begin(), dom_genes.end());

    for (int i = 0; i < NUMBER_OF_PARAMETERS/2; i++)
    {
        c[dom_genes[i]] = parameters[a][dom_genes[i]];
        if (rand()%100 <= 5)
        {
            if (rand()%2 == 1)
                c[dom_genes[i]] *= 0.7;
            else
                c[dom_genes[i]] *= 1.3;
        }

        d[dom_genes[i]] = parameters[a][dom_genes[i+5]];
        if (rand()%100 <= 5)
        {
            if (rand()%2 == 1)
                d[dom_genes[i]] *= 0.7;
            else
                d[dom_genes[i]] *= 1.3;
        }
    }

    int j = 0;
    for (int i = 0; i < NUMBER_OF_PARAMETERS/2; i++)
    {
        if (c[i] == NULL)
            c[i] = parameters[b][j];
    }

    for (int i = 0; i < NUMBER_OF_PARAMETERS/2; i++)
    {
        if (d[i] == NULL)
            d[i] = parameters[b][j];
    }

    c.push_back(0);
    d.push_back(0);
    
    return make_pair(c, d);
}
