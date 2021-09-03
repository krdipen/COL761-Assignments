#include<bits/stdc++.h>
using namespace std;

#define pp pair<int,int>
#define ll long long

ofstream outfile;
int cutoff;
// int Total;
// int X;
map<string,int> m;
vector<string> name;
vector<vector<int> > v;
vector<int> last;

bool isFreq(vector<pp> vp, int n){
    int count=0;
    for(auto x:vp){
        int a = x.first;
        int b = x.second; 
        // vector<int> v1=v[a]
        int len = last[a];
        for(int i=b; i<len; i++){
            if(v[a][i]==n) {
                count++;
                break;
            }
        }
        if(count>=cutoff) return true;
    }
    return false;
}

vector<pp> reduce(vector<pp> vp,int n){
    // vector<vector<int> > v2;
    vector<pp> v2;
    for(auto x:vp){
        int a = x.first;
        int b = x.second; 
        // vector<int> v1=v[a]
        int len = last[a];
        for(int i=b; i<len; i++){
            if(v[a][i]==n) {
                v2.push_back({a,i+1});
                break;
            }
        }
        // j++;
        // if(find(x.begin(),x.end(),n)!=x.end()) count++;
    }
    return v2;

}

void print(vector<int> v1){
    for(int x:v1) outfile<<name[x]<<" ";
    outfile<<"\n";
}


void solve(vector<pp> vp, int n, vector<int> v1, int n2){
    v1.push_back(n2);
    print(v1);
    vp = reduce(vp,n2);
    // cout<<n<<"\n";
    for(int i=0; i<n; i++) {
        if(isFreq(vp,i)){
            solve(vp,n,v1,i);
        }
    }
}

// void solve(vector<pp> vp, int n, vector<int> v1){
// }



int main(int argc,  char* argv[]){
    if(argc!=4) {cout<<"Please provide the file to read as argument\n"; return 0;}
    ifstream fread(argv[1]);
    if(!fread.is_open()){
        cout<<"input file not found"<<endl;
        return 0;
    }
    float X = stof(argv[2]);
    string line;
    string file_name = string(argv[3])+".txt";
    outfile.open(file_name);

    int i=0;
    // vector<string> name;
    // vector<int> freq;
    // vector<vector<int> > v;
    while(getline(fread,line)) {
        vector<int> v1;
        stringstream ss(line);
        string word;
        while(ss>>word) {
            auto temp = m.find(word);
            if(temp==m.end()){
                m[word] = i;
                name.push_back(word);
                v1.push_back(i);
                i++;
            }
            else{
                int a = m[word];
                v1.push_back(a);

            }
            // name.push_back(word);
        }
        v.push_back(v1);
    }
    int Total=v.size();
    // cout<<Total<<"\n";
    cutoff = ceil(1.0*X*Total/100);
    vector<int> v1;
    vector<pp> v2;
    i=0;
    for(auto x:v){
        v2.push_back({i,0});
        i++;
        last.push_back(x.size()); 
    }
    int n=name.size();
    for(i=0; i<n; i++) {
        if(isFreq(v2,i)){
            solve(v2,n,v1,i);
        }
    }


    // solve(v2,name.size(),v1);
    // print(v2);

    return 0;
}