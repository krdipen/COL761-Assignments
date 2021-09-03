#include<bits/stdc++.h>

using namespace std;

void parse(string line, ofstream & outfile){
    stack<string> st;
    string ans;
    stringstream input_stringstream(line);

    while (getline(input_stringstream,ans,';'))
    {
        if(ans=="<") {
            st.pop();
            string s = st.top();
            outfile<<s<<" ";
        }
        else {
            st.push(ans);
            outfile<<ans<<" ";
        }
    }
    outfile<<"\n";
}

int main(int argc,  char* argv[]){
    if(argc!=2) {cout<<"Please provide the file to read as argument\n"; return 0;}
    ifstream fread(argv[1]);
    if(!fread.is_open()){
        cout<<"input file not opened"<<endl;
        return 0;
    }
    string line;
    for(int i=0; i<16; i++){
        getline(fread,line);
    }
    ofstream outfile;
    outfile.open("paths_finished.dat");

    while(getline(fread,line)) {
        stringstream ss(line);
        string word;
        ss>>word>>word>>word>>word;
        parse(word,outfile);
    }

    return 0;
}