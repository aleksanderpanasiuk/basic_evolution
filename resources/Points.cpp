#include "Points.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>


/*  Generates set number of points and saves them in "resources/points.csv" file*/

Points::Points(int n_points)
{
    set_number_of_points(n_points);
}

void Points::set_number_of_points(int n_points)
{
    if (n_points < 0)
        throw std::invalid_argument("Number of points can't be negative");

    if (n_points > 10)
        throw std::invalid_argument("Number of points can't be larger than 10");

    number_of_points = n_points;
}


int Points::get_number_of_points()
{
    return number_of_points;
}

void Points::randomize_points()
{
    srand(time(0));

    std::vector<std::pair <double, double>> v;

    for (int i = 0; i < number_of_points; i++)
    {
        double x = ((rand() % 10000) / 1000.0);
        double y = ((rand() % 10000) / 1000.0) - 5;

        std::pair <double, double> p;
        p.first = x;
        p.second = y;

        v.push_back(p);
    }

    sort(v.begin(), v.end());
    std::ofstream output_file(file_path);
    output_file << "x, y\n";

    for (int i = 0; i < number_of_points; i++)
    {
        output_file << v[i].first << ", " << v[i].second << "\n";
    }

    output_file.close();
}


/*  Reads points from "resources/points.csv" file.
    If file does not exist runs randomize_points() function*/

void Points::read_points()
{
    std::ifstream input_file(file_path);

    if (input_file.fail())
    {
        randomize_points();

        std::ifstream input_file(file_path);
    }

    std::string header;
    input_file >> header >> header;

    for (int i = 0; i < number_of_points; i++)
    {
        std::string comma;
        input_file >> points[i].first >> comma >> points[i].second;
    }

    input_file.close();
}

std::ostream& operator<<(std::ostream& os, Points points)
{
    for (int i = 0; i < points.get_number_of_points(); i++)
    {
        os << std::fixed << std::setprecision(3)
        << i+1 << "\tx: " << points.points[i].first << "\ty: "
        << points.points[i].second << "\n";
    }

    return os;
}
