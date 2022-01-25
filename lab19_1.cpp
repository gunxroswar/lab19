#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<iomanip>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source(file);
    string text;
    char format[] =" %[^:]: %d %d %d ";
    while(getline(source,text)){
        int x,y,z;
        char *N;
        N = new char[25];
        const char * ch = text.c_str();
        sscanf(ch,format,N,&x,&y,&z);
        names.push_back(N);
        scores.push_back(x+y+z);
        grades.push_back(score2grade(x+y+z));

    }   
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string word;
    getline(cin,word);
    int loc = word.find(" ");
    command = word.substr(0,loc);
    key = word.substr(loc+1,word.size()-loc-1);   
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades,string &key){
    int N=names.size();
    bool k=false;
    for(int i =0;i<N;i++){
        if(toUpperStr(names[i])==toUpperStr(key)){
            k=true;
            if(k==true){
                cout << "---------------------------------\n";
                cout << names[i] << "'s score = " << scores[i] << "\n";
                cout << names[i] << "'s grade = " << grades[i] << "\n";
                cout << "---------------------------------\n";
            }
        }
    }
    if(k==false){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";  
    }
}
            


void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string &key){
    int N=names.size();
    bool k=false;
    cout << "---------------------------------\n";
    for(int i=0;i<N;i++){
        string g;
        g+=grades[i];
        if(key == g){
            k=true;
            if(k == true){
                cout << names[i] << " (" << scores[i] << ")\n";
            }
        }
    }
    if(k==false){
        cout << "Cannot found.\n";    
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
