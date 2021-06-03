#include "basic.h"
#include "initguid.h"
extern int num_city;
extern int num_salesman;
extern int num_exclusive;
extern vector<int> city_set;
extern vector<vector<double>> dist;

void initial_solution(solution& sol) {
    vector<int> node;
    int pointer;  
    int num;
    int rand1, rand2, temp;
    double delta, delta_temp;
    //the first step : build partial route
    for (int i = 0; i < num_salesman; ++i) {
        for (int j = 1; j <= num_city; ++j) {
            if(city_set[j] == (i + 1)) node.push_back(j);
        }
        num = node.size();
        //打乱节点顺序
        for (int j = 0; j < num; ++j) {
            rand1 = rand() % num;
            rand2 = rand() % num;
            while (rand1 == rand2) {
                rand2 = rand() % num;
            }
            temp = node[rand1];
            node[rand1] = node[rand2];
            node[rand2] = temp;
        }
        //a random city is used to initiate the greedy construction
        int pos = rand() % num;
        sol.solution[i][0] = node[pos];
        pointer = node[pos];
        sol.solution[i][pointer] = 0;
        node.erase(node.begin() + pos);
        //remaing cities insert greedily and probabilistically
        int loc;
        while (node.size()) {
            delta = DBL_MAX;
            num = node.size();
            pointer = 0;
            while (1) {
                delta_temp = dist[pointer][node[0]] + dist[node[0]][sol.solution[i][pointer]] - dist[pointer][sol.solution[i][pointer]];
                if (delta_temp < delta) {
                    delta = delta_temp;
                    loc = pointer;
                }
                pointer = sol.solution[i][pointer];
                if (pointer == 0) break;
            }
            temp = sol.solution[i][loc];
            sol.solution[i][loc] = node[0];
            sol.solution[i][node[0]] = temp;
            node.erase(node.begin());
        }
    }         
    //the second step : dispatch the shared cities
    for (int i = 1; i <= num_city; ++i) {
        if(city_set[i] == 0) node.push_back(i);
    }
    num = node.size();
    //int pos, row
    int pos = 0, row = 0;
    while (node.size()) {
        delta = DBL_MAX;
        for (int i = 0; i < num_salesman; ++i) {
            pointer = 0;
            while (1) {
                delta_temp = dist[pointer][node[0]] + dist[node[0]][sol.solution[i][pointer]] - dist[pointer][sol.solution[i][pointer]];
                if (delta_temp < delta) {
                    delta = delta_temp;
                    pos = pointer;
                    row = i;
                }
                pointer = sol.solution[i][pointer];
                if (pointer == 0) break;
            }
        }
        temp = sol.solution[row][pos];
        sol.solution[row][pos] = node[0];
        sol.solution[row][node[0]] = temp;
        node.erase(node.begin());
    }
    //compute cost
    for (int i = 0; i < num_salesman; ++i) {
        pointer = 0;
        while (1) {
            sol.cost += dist[pointer][sol.solution[i][pointer]];
            pointer = sol.solution[i][pointer];
            if (pointer == 0) break;
        }
    }
#ifdef DEBUG1
    for (int i = 0; i < sol.solution.size(); ++i) {
        for (auto x : sol.solution[i]) {
            cout << x << ' ';
        }
        cout << endl;
    }
    cout << sol.cost << endl;
#endif
}
