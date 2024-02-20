#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades)
{
    ifstream input(filename);
    string text;
    char name[100];
    int s1, s2, s3;
    char format[] = "%[^:]:%d %d %d";

    while (getline(input, text))
    {
        const char *texts = text.c_str();
        sscanf(texts, format, name, &s1, &s2, &s3);
        names.push_back(name);
        scores.push_back(s1 + s2 + s3);
        grades.push_back(score2grade(s1 + s2 + s3));
    }
}


void getCommand(string &command, string &key)
{
    cout << "Please input your command: ";
    cin >> command;
    if (toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME")
    {
        cin.ignore();
        getline(cin, key);
    }
}


void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, string key){
    bool found = false;
    for(size_t i = 0; i < names.size(); ++i){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < grades.size(); ++i){
        if(grades[i] == toupper(key[0])){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(found){
        cout << "---------------------------------\n";
    } else {
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
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