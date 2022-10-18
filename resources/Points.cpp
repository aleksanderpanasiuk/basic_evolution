#include "Points.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<iomanip>

using namespace std;

Points::Points()
{
    const int NUMBER_OF_POINTS = 10;
    pair<double, double> points[10];
}

void Points::randomize_points(int NUMBER_OF_POINTS)
{
    srand(time(0));

    vector<pair <double, double>> v;

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        double x = ((rand() % 10000) / 1000.0);
        double y = ((rand() % 10000) / 1000.0) - 5;

        pair <double, double> p;
        p.first = x;
        p.second = y;
        
        v.push_back(p);
    }

    sort(v.begin(), v.end());
    ofstream output_file("resources/points.txt");

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        output_file << v[i].first << " " << v[i].second << "\n";
    }

    output_file.close();
}

void Points::read_points(int NUMBER_OF_POINTS, pair<double, double> points[])
{
    ifstream input_file("resources/points.txt");

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        input_file >> points[i].first >> points[i].second;
    }

    input_file.close();
}

void Points::print_points(int NUMBER_OF_POINTS, pair<double, double> points[])
{
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        cout << fixed << setprecision(3) 
        << "x: " << points[i].first << "\ty: " << points[i].second << "\n";
    }
}
