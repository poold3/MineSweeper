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

const int NUM_MINES = 80;
const int NUM_ROWS = 32;
const int NUM_COLUMNS = 18;

void findEmptyCells(set<int> &minePositions, set<int> &cellsVisited, int position) {
    if (cellsVisited.find(position) == cellsVisited.end()) {
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = NUM_COLUMNS - 1;
        int left = -1;
        int right = 1;
        int top = NUM_COLUMNS * -1;
        int bottom = NUM_COLUMNS;
        int columnPosition = position % NUM_COLUMNS;
        cellsVisited.insert(position);

        if (position + top + left >= 0 && columnPosition != LEFT_EDGE) {
            if (minePositions.find(position + top + left) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + top + left);
            }
        }
        if (position + top >= 0) {
            if (minePositions.find(position + top) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + top);
            }
        }
        if (position + top + right >= 0 && columnPosition != RIGHT_EDGE) {
            if (minePositions.find(position + top + right) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + top + right);
            }
        }
        if (position + left >= 0  && columnPosition != LEFT_EDGE) {
            if (minePositions.find(position + left) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + left);
            }
        }
        if (position + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
            if (minePositions.find(position + right) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + right);
            }
        }
        if (position + bottom + left < (NUM_ROWS * NUM_COLUMNS) && columnPosition != LEFT_EDGE) {
            if (minePositions.find(position + bottom + left) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + bottom + left);
            }
        }
        if (position + bottom < (NUM_ROWS * NUM_COLUMNS)) {
            if (minePositions.find(position + bottom) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + bottom);
            }
        }
        if (position + bottom + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
            if (minePositions.find(position + bottom + right) == minePositions.end()) {
                findEmptyCells(minePositions, cellsVisited, position + bottom + right);
            }
        }

    }

    return;
}

int findOpenSpaces(set<int> &minePositions, int position) {
    const int LEFT_EDGE = 0;
    const int RIGHT_EDGE = NUM_COLUMNS - 1;
    int left = -1;
    int right = 1;
    int top = NUM_COLUMNS * -1;
    int bottom = NUM_COLUMNS;

    int columnPosition = position % NUM_COLUMNS;
    int neighborCells = 0;
    int neighborMines = 0;

    if (position + top + left >= 0 && columnPosition != LEFT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + top + left) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + top >= 0) {
        ++neighborCells;
        if (minePositions.find(position + top) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + top + right >= 0 && columnPosition != RIGHT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + top + right) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + left >= 0  && columnPosition != LEFT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + left) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + right) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + bottom + left < (NUM_ROWS * NUM_COLUMNS) && columnPosition != LEFT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + bottom + left) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + bottom < (NUM_ROWS * NUM_COLUMNS)) {
        ++neighborCells;
        if (minePositions.find(position + bottom) != minePositions.end()) {
            ++neighborMines;
        }
    }
    if (position + bottom + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
        ++neighborCells;
        if (minePositions.find(position + bottom + right) != minePositions.end()) {
            ++neighborMines;
        }
    }

    return neighborCells - neighborMines;
}

set<int> createMinePositions() {
    /*
    This function will randomly generate positions for mines in our keyField.
    The only stipulation is that no empty cells can be separated from other empty cells.
    This would result in an unsolvable field.
    */
    const int LEFT_EDGE = 0;
    const int RIGHT_EDGE = NUM_COLUMNS - 1;
    int left = -1;
    int right = 1;
    int top = NUM_COLUMNS * -1;
    int bottom = NUM_COLUMNS;

    bool found = false;
    set<int> minePositions;
    while (found == false) {
        minePositions.clear();
        /* Here we will generate mine positions. These positions will not cause the selected position
        or any of the neighbor positions to be completely surrounded by mines. Basically, we are 
        preventing the generation of something like this:

        [*][*][*]
        [*][*][*]
        [*][*][*]

        [*][*][*]
        [*][ ][*]
        [*][*][*]

        or something like this in a corner.

        [*][*]
        [*][*]

        [ ][*]
        [*][*]

        */
        while (minePositions.size() < NUM_MINES) {
            int position = rand() % (NUM_ROWS * NUM_COLUMNS);
            if (minePositions.find(position) == minePositions.end()) {
                int openSpaces = findOpenSpaces(minePositions, position);
                if (openSpaces >= 1) {
                    int columnPosition = position % NUM_COLUMNS;
                    bool addMine = true;
                    //There are openspaces around this position. But if we add a mine here, will it surround another cell?
                    if (position + top + left >= 0 && columnPosition != LEFT_EDGE) {
                        if (findOpenSpaces(minePositions, position + top + left) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + top >= 0) {
                        if (findOpenSpaces(minePositions, position + top) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + top + right >= 0 && columnPosition != RIGHT_EDGE) {
                        if (findOpenSpaces(minePositions, position + top + right) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + left >= 0  && columnPosition != LEFT_EDGE) {
                        if (findOpenSpaces(minePositions, position + left) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
                        if (findOpenSpaces(minePositions, position + right) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + bottom + left < (NUM_ROWS * NUM_COLUMNS) && columnPosition != LEFT_EDGE) {
                        if (findOpenSpaces(minePositions, position + bottom + left) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + bottom < (NUM_ROWS * NUM_COLUMNS)) {
                        if (findOpenSpaces(minePositions, position + bottom) <= 1) {
                            addMine = false;
                        }
                    }
                    if (position + bottom + right < (NUM_ROWS * NUM_COLUMNS) && columnPosition != RIGHT_EDGE) {
                        if (findOpenSpaces(minePositions, position + bottom + right) <= 1) {
                            addMine = false;
                        }
                    }

                    if (addMine == true) {
                        minePositions.insert(position);
                    }

                }
            }
        }

        /* Before we can submit these positions, we need to ensure that there are no groups of
        empty cells that are cut off from the other empty cells by a chain of mines. This would 
        result in an unsolvable field. We are preventing something like this:
        
        [ ][*][*][*][*][ ]
        [*][*][ ][ ][*][*]
        [ ][*][*][*][*][ ]
        [ ][ ][*][ ][ ][*]
        
        While no cell is completely surrounded by mines, the 2 empty cells in the middle will be 
        unsolvable because no number cell outside the mines will give any information on the middle
        cells.

        We will only run this check once per loop because of the unlikelyhood of generating a structure
        like this on a normal minefield of only 100 mines. If you were to generate a field with 200 or 
        300 mines, this method will not be the most efficient.

        An easy way to check that no structures like this occur is by traveling through all empty cells
        through their connections to each other. If we iterate through all the cell positions, each 
        position should either be in the minePositions or in the cellsVisited. If a position is not 
        in either of those, we know that there exists a structure like above where empty cells were 
        not accessible to other empty cells on the field. A playable field has all empty cells being
        connected either horizontally, vertically, or diagonally.
        
        */
        set<int> cellsVisited;
        int position;
        //Find an empty cell from which to begin mapping.
        for (int i = 0; i < NUM_ROWS * NUM_COLUMNS; ++i) {
            if (minePositions.find(i) == minePositions.end()) {
                position = i;
                break;
            }
        }
        //Find all empty cells connected to this one.
        findEmptyCells(minePositions, cellsVisited, position);
        bool allCellsPresent = true;
        //Determine if all cells are present
        for (int i = 0; i < NUM_ROWS * NUM_COLUMNS; ++i) {
            if (cellsVisited.find(i) == cellsVisited.end() && minePositions.find(i) == minePositions.end()) {
                allCellsPresent = false;
                break;
            }
        }
        if (allCellsPresent == true) {
            found = true;
        }

    }
    return minePositions;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        //We will create out own custom minefield.
        srand (time(NULL));
        set<int> minePositions = createMinePositions();
        vector<char> values;
        for (int i = 0; i < (NUM_ROWS * NUM_COLUMNS); ++i) {
            if (minePositions.find(i) == minePositions.end()) {
                values.push_back(' ');
            }
            else {
                values.push_back('*');
            }
        }
        Field keyField(NUM_ROWS, NUM_COLUMNS, values);
        keyField.toString();
        cout << endl;
        //Generate Number values around each mine in the field.
        keyField.generateNumberCells();
        //Generate our gameField with a 'c' on our starting position
        Field gameField;
        try {
            gameField = keyField.generateGameField(NUM_ROWS, NUM_COLUMNS);
        }
        catch (exception& e) {
            cout << endl << e.what() << endl;
            return 0;
        }
        
        cout << "The Field:" << endl << endl;
        gameField.toString();
        cout << endl << "The c is where the solver will \"click\" first. Press enter to progress through the solver." << endl;
        string answer;
        cout << endl << "Press Enter . . ." << endl << endl;
        getline(cin, answer);
        gameField.firstClick(keyField);
        bool solved = false;
        bool skip = false;
        while (solved == false) {
            cout << endl;
            gameField.toString();
            if (skip == false) {
                cout << endl << "Press Enter . . ." << endl << endl;
                getline(cin, answer);
                if (answer == "c") {
                    skip = true;
                }
            }

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
                    cout << "Trying Deductions" << endl;
                    getline(cin, answer);
                    set<int> newClickPositions;
                    gameField = gameField.deduction(newClickPositions);
                    if (newClickPositions.size() == 0) {
                        break;
                    }
                    else {
                        cout << "DEDUCTION!" << endl;
                        try {
                            gameField.runClicks(keyField, newClickPositions);
                        }
                        catch(exception& e) {
                            cout << endl << e.what() << endl << endl;
                            break;
                        }
                    }
                }
            }
        }

        if (solved == true) {
            gameField.toString();
            cout << endl << "Solved!" << endl << endl;
        }
        else {
            gameField.toString();
            cout << endl << "That's a tough MineField! We couldn't crack it! At this point, the solution is only knowable if you were to guess." << endl << endl;
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
            return 0;
        }
        outfile.close();
        cout << inputFile << " has been updated." << endl;
        return 0;
    }

    else {
        cout << "Incorrect number of arguments provided." << endl;
        return 0;
    }
    

    return 0;
}