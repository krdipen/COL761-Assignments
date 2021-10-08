#include<bits/stdc++.h>
using namespace std;
#include "ap.h"
#include "linalg.h"


// wget https://www.alglib.net/translator/re/alglib-3.17.0.cpp.gpl.zip
// unzip alglib-3.17.0.cpp.gpl.zip

void readData_old(vector<vector<string>> &dat, string datafile){
	ifstream inputFile;
	inputFile.open(datafile);
	if(inputFile.is_open()){
		string tp;
		int linec = 0;
		while(getline(inputFile,tp)){
			vector<string> newLine;
			istringstream ss(tp);
			string w;
			while(ss>>w) {
				// float a = stof(w);
				string a = w;
				newLine.push_back(a);
			}
			dat.push_back(newLine);
			// if(++linec == 10) break;
		}
	}
	inputFile.close();
}
																																																																																

int main(int argc , char* argv[]){

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	if(argc<2) { cout << "Argument missing" << endl; return -1;}
	
	string datafile = argv[1];
	// readData_old(dat, datafile);
	alglib::real_2d_array dat;

	alglib::read_csv(datafile.c_str(), ' ', 1, dat);

	alglib::ae_int_t dsize = dat.rows();
	alglib::ae_int_t inputDimension = dat.cols();
	alglib::ae_int_t dim = 5;
	double epsilon = 0.001;
	alglib::ae_int_t maxiters = 100;
	alglib::real_1d_array s2;
	alglib::real_2d_array v;
	alglib::pcatruncatedsubspace(dat, dsize, inputDimension, dim, epsilon, maxiters, s2, v); 


	return 0;


}
