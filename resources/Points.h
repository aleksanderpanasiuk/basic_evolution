#ifndef POINTS_H
#define POINTS_H
#include <iostream>

class Points
{
    private:
        int number_of_points;
        std::string file_path = "resources/points.csv";

    public:
        Points(int n_points);
        std::pair<double, double> points[10];
        void set_number_of_points(int n_points);
        int get_number_of_points();
        void randomize_points();
        void read_points();
        void print_points();
        friend std::ostream& operator<<(std::ostream& os, Points points);
};

std::ostream& operator<<(std::ostream& os, Points points);

#endif
