#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Field.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cout << "Error! Please inlcude MineSweeper File." << endl;
        return 0;
    }
    const string inputFile = argv[1];

    cout << "**Welcome to your MineSweeper Helper!" << endl;
    cout << "**Would you like to load a new MineField?(Y/n)";
    string newField;
    getline(cin, newField);
    if (newField == "Y" || newField == "Yes" || newField == "y" || newField == "yes") {
        // ofstream out;
        // out.open(inputFile);
        // if (out.is_open()) {
        //     out << "Testing" << endl;
        //     cout << "Successfully wrote to inputfile." << endl;
        // }
        // out.close();


    }
    else {
        cout << "No." << endl;
    }


    return 0;
}