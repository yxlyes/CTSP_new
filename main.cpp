#include "basic.h"
#include "read.h"
int num_city;                //the number of cities(except dopot 0)
int time_length;
int seed;

int num_salesman;
int num_exclusive;
vector<int> city_set;
vector<vector<double>> dist;

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
    
    cout << "OK";
    return 0;
}