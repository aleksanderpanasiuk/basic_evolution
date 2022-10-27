#include "Points.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<iomanip>


/*  Generates set number of points and saves them in "resources/points.txt" file*/

void Points::randomize_points()
{
    srand(time(0));

    std::vector<std::pair <double, double>> v;

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        double x = ((rand() % 10000) / 1000.0);
        double y = ((rand() % 10000) / 1000.0) - 5;

        std::pair <double, double> p;
        p.first = x;
        p.second = y;
        
        v.push_back(p);
    }

    sort(v.begin(), v.end());
    std::ofstream output_file("resources/points.txt");

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        output_file << v[i].first << " " << v[i].second << "\n";
    }

    output_file.close();
}


/*  Reads points from "resources/points.txt" file.
    If file does not exist runs randomize_points() function*/

void Points::read_points()
{
    std::ifstream input_file("resources/points.txt");

    if (input_file.fail())
    {
        randomize_points();

        std::ifstream input_file("resources/points.txt");
    }

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        input_file >> points[i].first >> points[i].second;
    }

    input_file.close();
}


/*  Prints coordinates of every point to standard output*/

void Points::print_points()
{
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        std::cout << std::fixed << std::setprecision(3) 
        << i+1 << "\tx: " << points[i].first << "\ty: " << points[i].second << "\n";
    }
}
