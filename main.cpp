#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Field.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cout << "Error! Please include MineSweeper Field as command line argument." << endl;
        cout << "Example: ./sweep input.txt" << endl;
        cout << endl;
        ifstream in;
        string inputLine;
        cout << "Notes on MineSweeper Field:" << endl;
        in.open("notes.txt");
        if (in.is_open()) {
            while(getline(in, inputLine)) {
                cout << inputLine << endl;
            }
        }
        else {
            cout << "Not found. Please make sure your directory contains \"notes.txt\"." << endl;
            cout << "You can find all program files at https://github.com/poold3/MineSweeper" << endl;
        }
        in.close();
        cout << endl;
        cout << "Example Field:" << endl;
        in.open("example.txt");
        if (in.is_open()) {
            while(getline(in, inputLine)) {
                cout << inputLine << endl;
            }
        }
        else {
            cout << "Not found. Please make sure your directory contains \"example.txt\"." << endl;
        }
        in.close();
        cout << endl << "Exiting!" << endl;
        return 0;
    }
    const string inputFile = argv[1];
    Field field;

    ifstream infile;
    string inputLine;
    infile.open(inputFile);
    if (infile.is_open()) {
        cout << "Current Field:" << endl;
        while(getline(infile, inputLine)) {
            cout << inputLine << endl;
        }
    }
    else {
        cout << "Error! " << inputFile << " was unable to be opened." << endl << endl;
        cout << "Exiting!" << endl;
        return 0;
    }
    infile.close();

    

    return 0;
}