#ifndef BASIC_H
#define BASIC_H

#define DEBUG

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cfloat>
using namespace std;

#define P_i   10   //  greedy probability in initial solution
#define O_max 50   //  search depth of SbTS
#define P_s   30   //  select probability in intra-route optimization
#define T_l   0.3  //  parameter of the tabu tenure of STS
#define T_    50   //  used to define the destruction probability
#define P_a   40   //  greedy probability in local optima escaping
struct solution {
    vector<vector<int>> solution;
    vector<vector<int>> solution_reverse;
    double cost;
};

#endif