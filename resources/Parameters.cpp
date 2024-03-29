#include "Parameters.h"


Parameters::Parameters(int population_size, int number_of_parameters) :
    population_size(population_size), number_of_parameters(number_of_parameters)
{
    for (int i = 0; i < population_size; i++)
    {
        std::vector<double> v(number_of_parameters+1, 0);
        parameters.push_back(v);
    }
}

/*  Changes every parameter value to random */

void Parameters::fill_random()
{
    for (int i = 0; i < population_size; i++)
    {
        for (int j = 0; j < number_of_parameters; j++)
        {
            double random_number = ((rand() % 2000000) / 10000.0) - 100;
            parameters[i][j] = random_number;
        }

        parameters[i][10] = 0;
    }
}


/*  Prints n sets of parameters to standart output */

void Parameters::print_top_parameters(int n=10, bool only_fitness=false)
{
    for (int i = 0; i < std::min(n, population_size); i++)
    {
        std::cout << i << ": ";

        if (!only_fitness)
        {
            for (int j = 0; j < number_of_parameters; j++)
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

double Parameters::calculate_function(double x, std::vector<double>& par)
{
    const double PI = 3.1415;
    double y = par[0] * sin((par[1]*x + par[2])*PI/180);
    y += par[3] * sin((par[4]*x + par[5])*PI/180);
    y += par[6] * sin((par[7]*x + par[8])*PI/180);
    y += par[9];

    return y;
}


/*  Calculates difference of given function and points for the same x */

void Parameters::calculate_fitness(std::vector<std::pair<double, double>>& points)
{
    for (int i = 0; i < population_size; i++)
    {
        parameters[i][number_of_parameters] = 0;

        for (std::pair<double, double>& point : points)
        {
            double x = point.first;
            double y = calculate_function(x, parameters[i]);
            double point_y = point.second;
            double fitness = std::abs(point_y - y);

            parameters[i][number_of_parameters] += (fitness * fitness);
        }

        // parameters[i][number_of_parameters] /= no_points;
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


/*  Writes value of all parameters to file_path file */

void Parameters::write_to_file(std::string file_path)
{
    std::ofstream output_file(file_path);

    output_file << "a1,k1,p1,a2,k2,p2,a3,k3,p3,c,fitness\n";

    for (int i = 0; i < population_size; i++)
    {
        for (int j = 0; j < number_of_parameters; j++)
        {
            output_file << parameters[i][j] << ", ";
        }

        output_file << parameters[i][number_of_parameters] << "\n";
    }

    output_file.close();
}


/*  Reads value of parameters from "resources/parameters.csv" file.
    If the file does not exist function fills vector of parameters with zeroes.
*/

void Parameters::read_from_file(std::string file_path)
{
    std::ifstream input_file(file_path);

    // File not found = randomize parameters
    if (input_file.fail())
        fill_random();
    else
    {
        std::string header;
        input_file >> header;

        for (int i = 0; i < population_size; i++)
        {
            for (int j = 0; j <= number_of_parameters; j++)
            {
                std::string comma;
                input_file >> parameters[i][j] >> comma;
            }
        }

        input_file.close();
    }
}


/*  Fills last n rows of parameters with zeroes */

void Parameters::kill_bottom(int creatures_to_kill)
{
    for (int i = population_size-creatures_to_kill; i < population_size; i++)
    {
        for (int j = 0; j <= number_of_parameters; j++)
            parameters[i][j] = 0;
    }

    pairing(creatures_to_kill);
}


/*  Chooes random pairs of vectors and calls mating() with them as arguments */

void Parameters::pairing(int n)
{
    std::vector<int> population;
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < population_size-n; i++)
        population.push_back(i);

    random_shuffle(population.begin(), population.end());

    for (int i = 0; i < population_size-n; i+= 2)
    {
        pairs.push_back(std::make_pair(population[i], population[i+1]));
    }

    for (int i = 0; i < (population_size-n)/2; i++)
    {
        std::pair<std::vector<double>, std::vector<double>> p = mating(pairs[i].first, pairs[i].second);

        parameters[n + (i*2)] = p.first;
        parameters[n + (i*2)+1] = p.second;
    }
}


/*  Calculate mutation value randombly.
    25% chance for mutation to occur and 50%
    chance for it to make the value lower and
    50% for making it higher.
*/

double Parameters::mutation_result()
{
    double mutation_value = 1;
    int chance_for_mutation = rand() % 100;

    if (25 >= chance_for_mutation)
    {
        if (1 == rand()%2)
            mutation_value = 0.7;
        else
            mutation_value = 1.5;
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

    for (int i = 0; i < number_of_parameters; i++)
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

    return {c, d};
}
