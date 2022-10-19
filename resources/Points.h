#ifndef POINTS_H
#define POINTS_H
#include<iostream>

class Points
{
    public:
        const int NUMBER_OF_POINTS = 10;
        std::pair<double, double> points[10];
        void randomize_points();
        void read_points();
        void print_points();
};

#endif
