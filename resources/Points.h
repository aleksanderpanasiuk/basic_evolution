#ifndef POINTS_H
#define POINTS_H
#include<iostream>

class Points
{
    public:
        Points();
        const int NUMBER_OF_POINTS = 10;
        std::pair<double, double> points[10];
        void randomize_points(int);
        void read_points(int, std::pair<double, double>[]);
        void print_points(int, std::pair<double, double>[]);
};

#endif
