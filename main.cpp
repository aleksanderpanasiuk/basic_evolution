#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include "resources/Points.h"

using namespace std;

const int POPULATION_SIZE = 200, NUMBER_OF_PARAMETERS = 10;
double parametry[POPULATION_SIZE][NUMBER_OF_PARAMETERS];

void fill_random()
{
    srand(time(0));

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            double random_number = ((rand() % 20000) / 100.0) - 100;
            parametry[i][j] = random_number;
        }
    }
}

void print_top_parameters(int n)
{
    for (int i = 0; i < min(n, POPULATION_SIZE); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < NUMBER_OF_PARAMETERS; j++)
        {
            cout << parametry[i][j] << " | ";
        }

        cout << "\n";
    }
}

int main()
{
    // fill_random();
    Points points;

    points.randomize_points(points.NUMBER_OF_POINTS);
    points.read_points(points.NUMBER_OF_POINTS, points.points);
    points.print_points(points.NUMBER_OF_POINTS, points.points);

    return 0;
}