#include "Parameters.h"
#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<vector>


/*  Fills parameters vector wtich vectors of zereos */

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


/*  Changes every parameter value to random */

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


/*  Prints n sets of parameters to standart output */

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


/*  Calculates f(x) function for:
    f(x) = a1 * sin(k1x+p1) + a2 * sin(k2x+p2) + a3 * sin(k3*x+p3) + c
*/

double Parameters::calculate_function(double x, std::vector<double> par)
{
    const double PI = 3.1415;
    double y = par[0] * sin((par[1]*x + par[2])*PI/180);
    y += par[3] * sin((par[4]*x + par[5])*PI/180);
    y += par[6] * sin((par[7]*x + par[8])*PI/180);
    y += par[9];

    return y;
}


/*  Calculates difference of given function and points for the same x */

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


/*  Sorts vector of parameters based on their fitness */

void Parameters::fitness_sort()
{
    sort(parameters.begin(), parameters.end(), 
    [] (const std::vector<double> &a, const std::vector<double> &b)
    {
        return a[10] < b[10];
    });
}



/*  Writes value of all parameters to "resources/parameters.txt" file */

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


/*  Reads value of parameters from "resources/parameters.txt" file.
    If the file does not exist function fills vector of parameters with zeroes.
*/

void Parameters::read_from_file()
{
    std::ifstream input_file("resources/parameters.txt");

    // File not found = fill parameters with zero
    if (input_file.fail())
    {
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
            {
                parameters[i][j] = 0;
            }
        }        
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
        {
            input_file >> parameters[i][j];
        }
    }

    input_file.close();
}


/*  Fills last n rows of parameters with zeroes */

void Parameters::kill_bottom(int n)
{
    for (int i = POPULATION_SIZE-n; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j <= NUMBER_OF_PARAMETERS; j++)
            parameters[i][j] = 0;
    }

    pairing(n);
}


/*  Chooes random pairs of vectors and calls mating() with them as arguments */

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


/*  Calculate mutation value randombly.
    5% chance for mutation to occur and 50%
    chance for it to make the value lower and 
    50% for making it higher.
*/

double Parameters::mutation_result()
{
    srand(time(0));

    double mutation_value = 1;
    int chance_for_mutation = rand() % 100;

    if (5 <= chance_for_mutation)
    {
        if (1 == rand()%2)
            mutation_value = 0.7;
        else
            mutation_value = 1.3;
    }

    return mutation_value;

}

/*  Chooses random genes from both parants and creates a pair of parameters
    with random chance to mutate
*/

std::pair<std::vector<double>, std::vector<double>> Parameters::mating(int a, int b)
{
    std::vector<double> c;
    std::vector<double> d;
    srand(time(0));

    for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
    {
        if (0 == rand()%2)
        {
            double new_gene_C = parameters[a][i] * mutation_result();
            c.push_back(new_gene_C);

            double new_gene_D = parameters[b][i] * mutation_result();
            d.push_back(new_gene_D);
        }
        else
        {
            double new_gene_C = parameters[b][i] * mutation_result();
            c.push_back(new_gene_C);

            double new_gene_D = parameters[a][i] * mutation_result();
            d.push_back(new_gene_D);
        }
    }

    c.push_back(0);
    d.push_back(0);
    
    return make_pair(c, d);
}
