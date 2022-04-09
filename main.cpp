#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "Scanner.h"
#include "Parser.h"
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
            cout << "You can find all program files at https://github.com/poold3/MineSweeper" << endl;
        }
        in.close();
        cout << endl << "Exiting!" << endl;
        return 0;
    }

    //Load inputFile and verify that it can be opened
    const string inputFile = argv[1];
    ifstream infile;
    string inputLine;
    infile.open(inputFile);
    if (infile.is_open()) {
        cout << "Input Field:" << endl;
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

    //Run Scanner on inputFile to verify validity of characters
    Scanner scanner(inputFile);
    try {
        cout << "\nRunning scan on field characters . . ." << endl;
        scanner.scanField();
        cout << "\nField scan complete! No invalid characters detected." << endl;
    }
    catch(exception& e) {
        cout << endl << e.what() << endl << endl;
        cout << "Exiting!!" << endl;
        return 0;
    }
    
    //Run Parser on tokens to verify validity of character order
    queue<char> tokens = scanner.getTokens();
    Parser parser(tokens);
    try {
        cout << "\nRunning scan on field character order . . ." << endl;
        parser.scanTokens();
        cout << "\nField scan complete! All characters are in the correct order." << endl;
    }
    catch(exception& e) {
        cout << endl << e.what() << endl << endl;
        cout << "Exiting!" << endl;
        return 0;
    }

    //Get all neccessary information and create the minefield
    int rows = scanner.getRows();
    int columns = scanner.getColumns();
    vector<char> values = parser.getValues();
    Field field(rows, columns, values);

    cout << "\nLoaded Field:" << endl;
    field.toString();
    cout << endl;
    Field newField = field.evaluate();

    return 0;
}