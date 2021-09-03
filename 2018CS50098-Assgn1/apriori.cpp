#include<bits/stdc++.h>
using namespace std;

bool ascii_comp(int a, int b){
	string sa = to_string(a), sb = to_string(b);
	return sa<sb;
}

int main(int argc , char* argv[]){

	auto start = clock();
	// time_t start, end;
	
	if(argc<4) { cout << "Argument missing" << endl; return -1;}
	
	string datafile = argv[1];
	string X_string = argv[2];
	string opfilename = argv[3];

	double x = stod(X_string);
	x = x/100;
	int trans = 0;

	vector<set<vector<int> > > F;			// F_i contains frequent itemset of size (i+1);
	
	map<vector<int>,int> F0;
	int support = 0;

	ifstream inputFile;	
	inputFile.open(datafile);
	if(inputFile.is_open()){
		map<int,int> m;
		string tp;
		// int linec = 0;
		while(getline(inputFile,tp)){
			trans++;
			istringstream ss(tp);
			string w;
			while(ss>>w) {
				int a = stoi(w);
				m[a]++;
			}
			// if(++linec == 100) break;
		}
		support = ceil(x*trans);
		set<vector<int> > s;
		for(auto &el: m){
			if(el.second>=support){
				s.insert({el.first});
			}
		}
		F.push_back(s);
	}
	inputFile.close();

	bool exiter = false;
	for(int i = 1 ; (int)F[i-1].size()!= 0 ; i++){	// size of new is (i+1);

		// cout << "i : " << i << endl;
		
		set<vector<int> > &Fim1 = F[i-1];
		map<vector<int>,int> candidates;

		int cand_gen_loop = 0;
		int prune_one_count = 0;
		int prune_two_count = 0;

		for(auto j = Fim1.begin() ; j!=Fim1.end() ; j++){
			for(auto k = next(j) ; k!=Fim1.end() ; k++){

				vector<int> fir = (*j);
				vector<int> sec = (*k);

				bool flag = false;
				vector<int> cand_gen(i+1);
				for(int iter = 0 ; iter<i-1 ; iter++){
					if(fir[iter] != sec[iter]) {flag = true; break;}
					cand_gen[iter] = fir[iter];
				}
				if(flag) continue;
				if(fir[i-1] < sec[i-1]){
					cand_gen[i-1] = fir[i-1]; cand_gen[i] = sec[i-1];
				}
				else{
					cand_gen[i-1] = sec[i-1]; cand_gen[i] = fir[i-1];	
				}
				
				// prune 1 :
				// Iterate through the vector to create a 1 minus sized vector :
				// for all such vectors : remove if support is less than 0
				
				vector<int> vector_checker(i);
				for(int iter = 0; iter<i; iter++) {vector_checker[iter] = cand_gen[iter+1];}
				flag = false;
				for(int iter = 0 ; iter <i-1 ; iter ++){		// i-1 bcoz iter == i-1 corresponds to 'j' or 'k'
					if(Fim1.find(vector_checker) == Fim1.end()) {flag = true; break;}
					vector_checker[iter] = cand_gen[iter];
				}
				if(flag) continue;

				candidates[cand_gen] = 0;

				// time limit!
				auto end = clock();
				auto time = (float)(end-start);
				time /= CLOCKS_PER_SEC;
				if(time >= 48*60) {exiter=true;break;}
			}
			if(exiter) break;
		}

		// prune 2 :
		// go through all transactions : find count.

		// ifstream inputFile;
		bool exiter2 = false;
		inputFile.open(datafile);
		if(inputFile.is_open()){
			string tp;
			// int linec = 0;
			while(getline(inputFile,tp)){
				istringstream ss(tp);
				string w;
				vector<int> vi;
				while(ss>>w) {
					int a = stoi(w);
					vi.push_back(a);
				}
				for(auto &candidate : candidates){
					int iv = 0, iter = 0;
					while(iv<(int)vi.size() && iter<(int)candidate.first.size() ){
						if(vi[iv]>candidate.first[iter]) break;
						if(vi[iv]==candidate.first[iter]) iter++;
						iv++;
					}

					if(iter==i+1) candidates[candidate.first]++;
				}
				auto end = clock();
				auto time = (float)(end-start);
				time /= CLOCKS_PER_SEC;
				if(time >= 55*60) {exiter2=true;break;}
			}
			if(exiter2) break;
		}
		inputFile.close();

		bool exiter3 = false;
		set<vector<int> > si;
		for(auto &candidate : candidates){
			if(candidate.second >= support) si.insert(candidate.first);
			
			auto end = clock();
			auto time = (float)(end-start);
			time /= CLOCKS_PER_SEC;
			if(time >= 57*60) {exiter3=true; break;}
		}
		F.push_back(si);
		if(exiter || exiter2 || exiter3) break;
	}

	ofstream outdata;
	outdata.open(opfilename+".txt");
	if( !outdata ) { cerr << "Error : File "<<opfilename<<".txt could not be opened"; exit(1);}
	for(auto &Fi : F){
		for(auto v: Fi){
			sort(v.begin(),v.end(),ascii_comp);
			for(auto elem : v) { outdata << elem << " "; }
			outdata << endl;
		}
	}
	outdata.close();


}
