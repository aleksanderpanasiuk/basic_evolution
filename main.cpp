#include<iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include "resources/Points.h"
#include "resources/Parameters.h"

using namespace std;

int main()
{
    Points points;
    points.read_points();

    Parameters parameters;
    parameters.read_from_file();
    parameters.print_top_parameters(10, true);

    return 0;
}