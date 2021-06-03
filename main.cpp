#include "basic.h"
#include "read.h"
#include "initial_solution.h"
int num_city;                //the number of cities(except dopot 0)
int time_length;
int seed;

int num_salesman;
int num_exclusive;
vector<int> city_set;
vector<vector<double>> dist;

solution sol;
solution best_sol;
solution g_best_sol;
solution temp_sol;

void initial_array() {
    sol.solution.resize(num_salesman, vector<int>(num_city + 1, -1));
    sol.solution_reverse.resize(num_salesman, vector<int>(num_city + 1, -1));
    best_sol.solution.resize(num_salesman, vector<int>(num_city + 1, -1));
    g_best_sol.solution.resize(num_salesman, vector<int>(num_city + 1, -1));
}
int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "the input parameters in configuration are wrong" << endl;
        return 1;
    }
    num_city = atoi(argv[2]);
    time_length = atoi(argv[3]);
    seed = atoi(argv[4]);
    if (!build_instance(argv[1])) {
        cerr << "can't open instance file" << endl;
        return 1;
    }
    // srand(seed);
    srand(time(0));
    clock_t start = clock();
    initial_array();
    initial_solution(sol);
    cout << "OK";
    return 0;
}