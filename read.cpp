#include "basic.h"
#include "read.h"

extern int num_city;
extern int num_salesman;
extern int num_exclusive;
extern vector<int> city_set;
extern vector<vector<double>> dist;
bool build_instance(char* file_name) {
    ifstream file_in(file_name);
    city_set.resize(num_city + 1, 0);
    vector<double> x(num_city + 1), y(num_city + 1);     
    string name;
    int num;
    file_in >> name >> num >> num_salesman >> num_exclusive;
    if (num != num_city) {
        cerr << "the number of cities don't match" << endl;
        return false;
    }
    int set = 1;
    int count = 1;
    for (int i = 1; i <= num_city; ++i) {
        if (set > num_salesman) break;
        if (count <= num_exclusive && set <= num_salesman) {
            city_set[i] = set;
            ++count;
        } else {
            --i;
            count = 1;
            ++set;
        }
    }
    int number;
    for (int i = 0; i <= num_city; ++i) {
        file_in >> number >> x[i] >> y[i];
    }
    file_in.close();
    compute_distance(x, y);
    return true;
}

void compute_distance(vector<double>& x, vector<double>& y) {
    dist.resize(num_city + 1, vector<double>(num_city + 1));
    if (num_city <= 200 || (num_city > 900 && num_city < 5000)) {
        for (int i = 0; i <= num_city; ++i) {
            for (int j = 0; j <= num_city; ++j) {
                dist[i][j] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
            }
        }
    }
    if (num_city > 5000) {
        for (int i = 0; i <= num_city; ++i) {
            for (int j = 0; j <= num_city; ++j) {
                dist[i][j] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
            }
        }
    }
    if (num_city > 200 && num_city < 700) {
        double q1,q2,q3;
		double RRR = 6378.388;
		vector<double> latitude, longitude;
		// double latitude[num_v+1];
		// double longitude[num_v+1];
        latitude.resize(num_city + 1);
        longitude.resize(num_city + 1);
		double min;
		double deg;
		double PI=3.141592;
		for (int i=0;i<=num_city;i++){
			deg=int(x[i]);
			min=x[i]-deg;
			latitude[i]=PI * (deg + 5.0 * min / 3.0 ) / 180.0;
			deg=int(y[i]);
			min=y[i]-deg;
			longitude[i]=PI * (deg + 5.0 * min / 3.0 ) / 180.0;
		}
		for (int i=0;i<=num_city;i++)
			for (int j=0;j<=num_city;j++){
				q1 = cos( longitude[i] - longitude[j] );
				q2 = cos( latitude[i] - latitude[j] );
				q3 = cos( latitude[i] + latitude[j] );
				dist[i][j] = (int) ( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ) + 1.0);
			}
    }
}