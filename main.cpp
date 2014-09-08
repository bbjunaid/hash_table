#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

int main( int argc, char** argv ) {
    HashTable< string, vector<string> > mytable;
    vector<string> mississaugaList = {"Bilal", "Nabeel", "Saad"};
    mytable.insert("Mississauga", mississaugaList);
    
    vector<string>& tmp = mytable["Mississauga"];
    tmp.push_back("Sameer");
    mytable["Oakville"] = mytable["Mississauga"];
    mytable["Oakville"].push_back("Kareem");
    tmp = mytable["Oakville"];

    for(size_t i = 0; i < tmp.size(); ++i)
        cout << tmp[i] << " ";

    cout << endl;
}
