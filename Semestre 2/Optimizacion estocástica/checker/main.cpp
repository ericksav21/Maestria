#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	string path = "../instances/";
	string name;
	vector<string> types = {"Heuristic", "Random"};

	while(cin >> name) {
		for(int n = 0; n < 2; n++) {
			string ins_path = path + types[n] + "/" + name + "/Results_";

			double mean_fit_heur = 0.0, mean_fit_loc = 0.0;
			int mmin = 10000;
			double mean_heuris = 0.0, mean_local = 0.0, mean_total = 0.0;

			for(int i = 1; i <= 100; i++) {
				string instance = ins_path + to_string(i) + ".txt";
				ifstream file(instance.c_str());

				int fit_heuris, fit_ini, fit_local;
				double t_heuris, t_local, t_total;

				file >> fit_heuris >> fit_ini >> fit_local;
				file >> t_heuris >> t_local >> t_total;

				mmin = min(mmin, fit_local);
				mean_heuris += t_heuris;
				mean_local += t_local;
				mean_total += t_total;
				mean_fit_heur += fit_heuris;
				mean_fit_loc += fit_local;

				file.close();
			}

			mean_heuris /= 100.0;
			mean_local /= 100.0;
			mean_total /= 100.0;
			mean_fit_heur /= 100.0;
			mean_fit_loc /= 100.0;

			string r = "Results_" + name + "_" + types[n] + ".txt";
			ofstream out(r);
			out << "Fit min: " << mmin << endl;
			out << "Media heur: " << mean_heuris << endl;
			out << "Media local: " << mean_local << endl;
			out << "Media total: " << mean_total << endl;
			out << "Media fit heur: " << (int)mean_fit_heur << endl;
			out << "Media fit loc: " << (int)mean_fit_loc << endl;
			out.close();
		}
	}

	return 0;
}