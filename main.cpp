#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <stdlib.h>

#include "Scanner.h"
#include "Parser.h"
#include "Field.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        //We will create out own custom minefield.
        srand (time(NULL));
        set<int> minePositions;
        while (minePositions.size() < 75) {
            minePositions.insert(rand() % 576);
        }
        vector<char> values;
        for (int i = 0; i < 576; ++i) {
            if (minePositions.find(i) == minePositions.end()) {
                values.push_back(' ');
            }
            else {
                values.push_back('*');
            }
        }
        Field keyField(32, 18, values);
        //Generate Number values around each mine in the field.
        keyField.generateNumberCells();
        //keyField.toString();
        //Generate our gameField with a 'c' on our starting position
        Field gameField = keyField.generateGameField();
        
        cout << "The Field:" << endl << endl;
        gameField.toString();
        cout << endl << "The c denotes where the solver will \"click\" first. Press enter to progress through the solver." << endl;
        string answer;
        cout << "Press Enter . . ." << endl << endl;
        getline(cin, answer);
        gameField.firstClick(keyField);
        gameField.toString();
        cout << endl << "Press Enter . . ." << endl << endl;
        getline(cin, answer);
        bool solved = false;
        bool skip = false;
        while (solved == false) {
            set<int> clickPositions;
            gameField = gameField.evaluate(clickPositions);
            if (clickPositions.size() > 0) {
                try {
                    gameField.runClicks(keyField, clickPositions);
                }
                catch(exception& e) {
                    cout << endl << e.what() << endl << endl;
                    break;
                }
            }
            else {
                if (gameField.solved(keyField) == true) {
                    solved = true;
                }
                else {
                    cout << "That's a tough MineField! We couldn't crack it!" << endl << endl;
                    break;
                }
            }
            
            gameField.toString();
            if (skip == false) {
                cout << endl << "Press Enter . . ." << endl << endl;
                getline(cin, answer);
                if (answer == "c") {
                    skip = true;
                }
            }
            
        }

        if (solved == true) {
            cout << "Solved!" << endl << endl;
        }

        

    }

    else if (argc == 2) {
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
        set<int> clickPositions;
        Field newField = field.evaluate(clickPositions);

        cout << endl << endl << "Final Field." << endl;
        newField.toString();

        ofstream outfile;
        outfile.open(inputFile);
        if (outfile.is_open()) {
            outfile << newField.returnString();
        }
        else {
            cout << "Error! " << inputFile << " was unable to be opened." << endl << endl;
            cout << "Exiting!" << endl;
            return 0;
        }
        outfile.close();
        cout << inputFile << " has been updated." << endl;
        return 0;
    }

    else {
        return 0;
    }
    

    return 0;
}