#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <stdlib.h>

#include "Cell.h"

using namespace std;

class Field {
private:
    vector<Cell> cells;
    int rows;
    int columns;
    int left = -1;
    int right = 1;
    int top;
    int bottom;
    int minesFound = 0;
    int totalMines;

public:
    Field (int rows, int columns, vector<char> values, int totalMines) {
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i < rows * columns; ++i) {
            int rowPosition = i / columns;
            int columnPosition = i % columns;
            Cell cell(values.at(i), i, rowPosition, columnPosition);
            cells.push_back(cell);
        }
        this->top = columns * -1;
        this->bottom = columns;
        this->totalMines = totalMines;
    }
    Field (int rows, int columns, vector<Cell> cells, int totalMines) {
        this->rows = rows;
        this->columns = columns;
        this->cells = cells;
        this->top = columns * -1;
        this->bottom = columns;
        this->totalMines = totalMines;
    }

    Field() {
        this->rows = 0;
        this->columns = 0;
        this->top = 0;
        this->bottom = 0;
        this->totalMines = 0;
    }

    int size() {
        return cells.size();
    }

    vector<Cell> getCells() {
        return cells;
    }

    Cell& at(int rowPosition, int columnPosition) {
        return cells.at((rowPosition * columns) + columnPosition);
    }

    Cell& at(int position) {
        return cells.at(position);
    }

    Cell copyAt(int rowPosition, int columnPosition) {
        return cells.at((rowPosition * columns) + columnPosition);
    }

    Cell copyAt(int position) {
        return cells.at(position);
    }

    void setMinesFound(int minesFound) {
        this->minesFound = minesFound;
    }

    void foundMine() {
        ++minesFound;
    }

    int getMinesFound() {
        return minesFound;
    }

    int getTotalMines() {
        return totalMines;
    }

    void countMinesFound() {
        int mineNumber = 0;
        for (auto& cell : cells) {
            if (cell.isMine() == true) {
                ++mineNumber;
            }
        }
        minesFound = mineNumber;
    }

    void update(int rowPosition, int columnPosition, char value) {
        cells.at((rowPosition * columns) + columnPosition).update(value);
    }

    bool solved(Field &keyField) {
        //Returns true if the gameField matches the keyField
        vector<Cell> keyCells = keyField.getCells();
        bool solved = true;
        for (unsigned long i = 0; i < keyCells.size(); ++i) {
            if (keyCells.at(i).getValue() != cells.at(i).getValue()) {
                solved = false;
                break;
            }
        }

        return solved;
    }

    bool needMoreMines() {
        /* Return true if at least one number does not have sufficient mines. Return false if all numbers
        have sufficient mines 
        
        Iteratate through all number cells. See if number of mines present equals the value.
        */
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        for (auto& cell : cells) {
            if (cell.isNumber() == true) {
                int currentCellPosition = cell.getPosition();
                char value = cell.getValue();
                int iValue = value - '0';
                int numberOfMines = 0;
                if (currentCellPosition + top + left >= 0 && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + top + left).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (currentCellPosition + top >= 0) {
                    if (cells.at(currentCellPosition + top).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (currentCellPosition + top + right >= 0 && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE){
                    if (cells.at(currentCellPosition + top + right).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (currentCellPosition + left >= 0  && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + left).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                
                if (currentCellPosition + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                   if (cells.at(currentCellPosition + right).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                
                if (currentCellPosition + bottom + left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + left).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (currentCellPosition + bottom < static_cast<int>(cells.size())) {
                    if (cells.at(currentCellPosition + bottom).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (currentCellPosition + bottom + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + right).isMine() == true) {
                        ++numberOfMines;
                    }
                }
                if (numberOfMines < iValue) {
                    return true;
                }

            }
        }

        return false;
    }

    void toString() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cells.at((i * columns) + j).toString();
            }
            cout << endl;
        }
    }

    string returnString() {
        ostringstream out;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                out << cells.at((i * columns) + j).returnString();
            }
            out << endl;
        }

        return out.str();
    }

    void generateNumberCells() {
        //This function only exists for key fields. This function generates number values around mines.
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        int currentCellPosition = 0;
        for (auto& cell : cells) {
            if (cell.getValue() == ' ') {
                int numberValue = 0;

                if (currentCellPosition + top + left >= 0 && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + top + left).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + top >= 0) {
                    if (cells.at(currentCellPosition + top).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + top + right >= 0 && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE){
                    if (cells.at(currentCellPosition + top + right).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + left >= 0  && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + left).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + right).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + bottom + left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + left).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + bottom < static_cast<int>(cells.size())) {
                    if (cells.at(currentCellPosition + bottom).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (currentCellPosition + bottom + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + right).getValue() == '*') {
                        ++numberValue;
                    }
                }
                if (numberValue > 0) {
                    char value = numberValue + '0';
                    cell.update(value);
                }
            }
            ++currentCellPosition;
        }


    }

    static void mapEmptyPatchSize(vector<Cell> &cells, int position, int &size, set<int> &cellsVisited, int columns, bool skipCheck = false) {
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        int left = -1;
        int right = 1;
        int top = columns * -1;
        int bottom = columns;
        if (cellsVisited.find(position) == cellsVisited.end() || skipCheck == true) {
            cellsVisited.insert(position);
            ++size;
            if (position + top >= 0) {
                if (cells.at(position + top).getValue() == ' ') {
                    mapEmptyPatchSize(cells, position + top, size, cellsVisited, columns);
                }
            }
            if (position + left >= 0  && cells.at(position).getColumnPosition() != LEFT_EDGE) {
                if (cells.at(position + left).getValue() == ' ') {
                    mapEmptyPatchSize(cells, position + left, size, cellsVisited, columns);
                }
            }
            if (position + right < static_cast<int>(cells.size()) && cells.at(position).getColumnPosition() != RIGHT_EDGE) {
                if (cells.at(position + right).getValue() == ' ') {
                    mapEmptyPatchSize(cells, position + right, size, cellsVisited, columns);
                }
            }
            if (position + bottom < static_cast<int>(cells.size())) {
                if (cells.at(position + bottom).getValue() == ' ') {
                    mapEmptyPatchSize(cells, position + bottom, size, cellsVisited, columns);
                }
            }
        }
        return;
    }

    static void outlineEmptyPatch(vector<Cell> &cells, vector<Cell> keyCells, set<int> cellsVisited, int columns) {
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        int left = -1;
        int right = 1;
        int top = columns * -1;
        int bottom = columns;

        for (auto& position : cellsVisited) {
            if (position + top + left >= 0 && keyCells.at(position).getColumnPosition() != LEFT_EDGE) {
                if (keyCells.at(position + top + left).isNumber() == true) {
                    cells.at(position + top + left).update(keyCells.at(position + top + left).getValue());
                }
            }
            if (position + top >= 0) {
                if (keyCells.at(position + top).isNumber() == true) {
                    cells.at(position + top).update(keyCells.at(position + top).getValue());
                }
            }
            if (position + top + right >= 0 && keyCells.at(position).getColumnPosition() != RIGHT_EDGE){
                if (keyCells.at(position + top + right).isNumber() == true) {
                    cells.at(position + top + right).update(keyCells.at(position + top + right).getValue());
                }
            }
            if (position + left >= 0  && keyCells.at(position).getColumnPosition() != LEFT_EDGE) {
                if (keyCells.at(position + left).isNumber() == true) {
                    cells.at(position + left).update(keyCells.at(position + left).getValue());
                }
            }
            if (position + right < static_cast<int>(keyCells.size()) && keyCells.at(position).getColumnPosition() != RIGHT_EDGE) {
                if (keyCells.at(position + right).isNumber() == true) {
                    cells.at(position + right).update(keyCells.at(position + right).getValue());
                }
            }
            if (position + bottom + left < static_cast<int>(keyCells.size()) && keyCells.at(position).getColumnPosition() != LEFT_EDGE) {
                if (keyCells.at(position + bottom + left).isNumber() == true) {
                    cells.at(position + bottom + left).update(keyCells.at(position + bottom + left).getValue());
                }
            }
            if (position + bottom < static_cast<int>(keyCells.size())) {
                if (keyCells.at(position + bottom).isNumber() == true) {
                    cells.at(position + bottom).update(keyCells.at(position + bottom).getValue());
                }
            }
            if (position + bottom + right < static_cast<int>(keyCells.size()) && keyCells.at(position).getColumnPosition() != RIGHT_EDGE) {
                if (keyCells.at(position + bottom + right).isNumber() == true) {
                    cells.at(position + bottom + right).update(keyCells.at(position + bottom + right).getValue());
                }
            }
        }

        return;
    }

    Field generateGameField(const int NUM_ROWS, const int NUM_COLUMNS) {
        //This function only exists for key fields. This function generates a playable field.
        /*
            First, we need to find a good/random starting location. I want the starting location to have
        at least 10 empty cells.

            I am using a set to keep track of positions that we can still search. Erasing from a
        vector at beginning to middle positions is not very efficient.
        */
        set<int> positions;
        for (int i = 0; i < NUM_ROWS * NUM_COLUMNS; ++i) {
            positions.insert(i);
        }
        bool found = false;
        int startingPosition = 0;
        while (found == false) {
            if (positions.size() == 0) {
                string error = "No empty patch big enough to begin.";
                throw std::invalid_argument(error);
            }
            int position;
            int iterations = rand() % positions.size();
            int counter = 0;
            for (auto& pos : positions) {
                if (counter == iterations) {
                    position = pos;
                    break;
                }
                ++counter;
            }
            if (cells.at(position).getValue() == ' ') {
                
                /*We found an empty cell. Map out empty neighbor cells nearby to determine size of
                empty patch.*/
                int size = 0;
                set<int> cellsVisited;
                mapEmptyPatchSize(cells, position, size, cellsVisited, columns);
                if (size >= 10) {
                    startingPosition = position;
                    found = true;
                }
            }
            positions.erase(position);

        }
        /*We found our starting position. Now create a new field with all unknown cells and one 
        c value at starting position*/
        vector<char> values;
        for (int i = 0; i < (NUM_ROWS * NUM_COLUMNS); ++i) {
            if (i == startingPosition) {
                values.push_back('c');
            }
            else {
                values.push_back('#');
            }
        }

        Field gameField(NUM_ROWS, NUM_COLUMNS, values, totalMines);
        return gameField;
    }

    void firstClick(Field &keyField) {
        //Find the c cell
        int cPosition = 0;
        for (auto& cell : cells) {
            if (cell.getValue() == 'c') {
                cPosition = cell.getPosition();
                break;
            }
        }

        vector<Cell> keyCells = keyField.getCells();
        int size = 0;
        set<int> cellsVisited;
        //Map the empty patch and update the gameField
        mapEmptyPatchSize(keyCells, cPosition, size, cellsVisited, columns);
        for (auto& position : cellsVisited) {
            cells.at(position).update(' ');
        }
        
        //Find all numbers surrounding the empty patch and update the gameField with those numbers.
        outlineEmptyPatch(cells, keyCells, cellsVisited, columns);

        return;
    }

    void runClicks(Field &keyField, set<int> clickPositions) {
        vector<Cell> keyCells = keyField.getCells();

        for (auto& position : clickPositions) {
            if (keyCells.at(position).isNumber() == true) {
                cells.at(position).update(keyCells.at(position).getValue());
            }
            else if (keyCells.at(position).getValue() == ' ') {
                int size = 0;
                set<int> cellsVisited;
                mapEmptyPatchSize(keyCells, position, size, cellsVisited, columns);
                for (auto& position : cellsVisited) {
                    cells.at(position).update(' ');
                }
                outlineEmptyPatch(cells, keyCells, cellsVisited, columns);

            }
            else if (keyCells.at(position).isMine() == true) {
                string error = "KABOOM! You bumbed a mine which exploded and caused a massive chain reaction in which all of the mines exploded! You died :(";
                throw std::invalid_argument(error);
            }
            else {
                string error = "Something weird happened. Please retry.";
                throw std::invalid_argument(error);
            }
        }
        return;
    }

    void clearPossibleMines() {
        for (unsigned long i = 0; i < cells.size(); ++i) {
            cells.at(i).clearPossibleMines();
        }
    }

    void clearAdjacentNumberPositions() {
        for (unsigned long i = 0; i < cells.size(); ++i) {
            cells.at(i).clearAdjacentNumberPositions();
        }
    }

    void mapPossibleMinesAndNumbers() {
        //cout << "In mapping" << endl;
        int currentCellPosition = 0;
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        for (unsigned long i = 0; i < cells.size(); ++i) {
            if (cells.at(currentCellPosition).isNumber() == true) {
                //First outer ring. Looking for numbers and possible mines.
                if (currentCellPosition + top + left >= 0 && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + top + left).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + top + left);
                    }
                    else if (cells.at(currentCellPosition + top + left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + top + left);
                    }
                }
                if (currentCellPosition + top >= 0) {
                    if (cells.at(currentCellPosition + top).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + top);
                    }
                    else if (cells.at(currentCellPosition + top).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + top);
                    }
                }
                if (currentCellPosition + top + right >= 0 && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE){
                    if (cells.at(currentCellPosition + top + right).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + top + right);
                    }
                    else if (cells.at(currentCellPosition + top + right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + top + right);
                    }
                }
                if (currentCellPosition + left >= 0  && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + left).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + left);
                    }
                    else if (cells.at(currentCellPosition + left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + left);
                    }
                }
                
                if (currentCellPosition + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + right).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + right);
                    }
                    else if (cells.at(currentCellPosition + right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + right);
                    }
                }
                
                if (currentCellPosition + bottom + left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + left).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + bottom + left);
                    }
                    else if (cells.at(currentCellPosition + bottom + left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + bottom + left);
                    }
                }
                if (currentCellPosition + bottom < static_cast<int>(cells.size())) {
                    if (cells.at(currentCellPosition + bottom).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + bottom);
                    }
                    else if (cells.at(currentCellPosition + bottom).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + bottom);
                    }
                }
                if (currentCellPosition + bottom + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + bottom + right).possibleMine() == true) {
                        cells.at(currentCellPosition).addAdjacentPossibleMinePosition(currentCellPosition + bottom + right);
                    }
                    else if (cells.at(currentCellPosition + bottom + right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + bottom + right);
                    }
                }

                //Second outer ring. Looking only for numbers.
                if (currentCellPosition + 2*top + 2*left >= 0 && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE + 1) {
                    if (cells.at(currentCellPosition + 2*top + 2*left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*top + 2*left);
                    }
                }

                if (currentCellPosition + 2*top + left >= 0 && cells.at(currentCellPosition).getColumnPosition() != LEFT_EDGE) {
                    if (cells.at(currentCellPosition + 2*top + left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*top + left);
                    }
                }

                if (currentCellPosition + 2*top >= 0) {
                    if (cells.at(currentCellPosition + 2*top).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*top);
                    }
                }

                if (currentCellPosition + 2*top + right >= 0 && cells.at(currentCellPosition).getColumnPosition() != RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + 2*top + right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*top + right);
                    }
                }

                if (currentCellPosition + 2*top + 2*right >= 0 && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE - 1) {
                    if (cells.at(currentCellPosition + 2*top + 2*right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*top + 2*right);
                    }
                }

                if (currentCellPosition + top + 2*left >= 0 && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE + 1) {
                    if (cells.at(currentCellPosition + top + 2*left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + top + 2*left);
                    }
                }

                if (currentCellPosition + top + 2*right >= 0 && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE - 1) {
                    if (cells.at(currentCellPosition + top + 2*right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + top + 2*right);
                    }
                }

                if (currentCellPosition + 2*left >= 0 && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE + 1) {
                    if (cells.at(currentCellPosition + 2*left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*left);
                    }
                }

                if (currentCellPosition + 2*right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE - 1) {
                    if (cells.at(currentCellPosition + 2*right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*right);
                    }
                }

                if (currentCellPosition + bottom + 2*left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE + 1) {
                    if (cells.at(currentCellPosition + bottom + 2*left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + bottom + 2*left);
                    }
                }

                if (currentCellPosition + bottom + 2*right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE - 1) {
                    if (cells.at(currentCellPosition + bottom + 2*right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + bottom + 2*right);
                    }
                }

                if (currentCellPosition + 2*bottom + 2*left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE + 1) {
                    if (cells.at(currentCellPosition + 2*bottom + 2*left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*bottom + 2*left);
                    }
                }

                if (currentCellPosition + 2*bottom + left < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() > LEFT_EDGE) {
                    if (cells.at(currentCellPosition + 2*bottom + left).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*bottom + left);
                    }
                }

                if (currentCellPosition + 2*bottom < static_cast<int>(cells.size())) {
                    if (cells.at(currentCellPosition + 2*bottom).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*bottom);
                    }
                }

                if (currentCellPosition + 2*bottom + right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE) {
                    if (cells.at(currentCellPosition + 2*bottom + right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*bottom + right);
                    }
                }

                if (currentCellPosition + 2*bottom + 2*right < static_cast<int>(cells.size()) && cells.at(currentCellPosition).getColumnPosition() < RIGHT_EDGE - 1) {
                    if (cells.at(currentCellPosition + 2*bottom + 2*right).isNumber() == true) {
                        cells.at(currentCellPosition).addAdjacentNumberPosition(currentCellPosition + 2*bottom + 2*right);
                    }
                }
            }
            ++currentCellPosition;
        }
    }

    static void depthSearch(Field &newField, int position, set<int> &cellsVisited, set<int> &SCC, bool skipCheck = false) {
        
        if (skipCheck == true || cellsVisited.find(position) == cellsVisited.end()) {
            cellsVisited.insert(position);
            //Cell has not been visited
            
            //Get cell adjacent number and mine positions
            set<int> adjacentNumberPositions = newField.copyAt(position).getadjacentNumberPositions();
            set<int> adjacentPossibleMinePositions = newField.copyAt(position).getAdjacentPossibleMinePositions();
            
            //Visit all neighbors who are numbers
            for (auto& adjacentNumberPosition: adjacentNumberPositions) {

                //In each neighbor that is a number, get their adjacent mine positions
                set<int> neighborPossibleMinePositions = newField.copyAt(adjacentNumberPosition).getAdjacentPossibleMinePositions();
                //Search for similarities between neighbor adjacent mine positions and cell adjacent mine positions
                for (auto& adjacentMinePosition: adjacentPossibleMinePositions) {
                    if (neighborPossibleMinePositions.find(adjacentMinePosition) != neighborPossibleMinePositions.end()) {
                        //Shared possible mine cell! Explore in depth search, add to cells visited, and add to current SCC!
                        
                        depthSearch(newField, adjacentNumberPosition, cellsVisited, SCC);
                        SCC.insert(adjacentNumberPosition);

                    }
                }
            }
        }
        return;
    }

    static bool evaluateSCC(Field &newField, set<int> &SCC, set<int> &clickPositions, set<int> &minePositions, bool performingDeduction = false) {
        int changes = 0;
        int changeCounter = 1;
        int counter = 0;
        while (changes != changeCounter) {
            ++counter;
            changeCounter = changes;
            for (auto& position : SCC) {
                Cell currentCell = newField.at(position);
                char value = currentCell.getValue();
                int valueCopy = value - '0';
                vector<int> unknownPositions;
                set<int> possibleMinePositions = currentCell.getAdjacentPossibleMinePositions();
                for (auto& position2 : possibleMinePositions) {
                    if (newField.copyAt(position2).getValue() == '*') {
                        --valueCopy;
                    }
                    else if (newField.copyAt(position2).getValue() == '#') {
                        unknownPositions.push_back(position2);
                    }
                }
                if (valueCopy > 0 && valueCopy == static_cast<int>(unknownPositions.size())) {
                    //Convert all '#' around cell to '*'
                    for (unsigned long i = 0; i < unknownPositions.size(); ++i) {
                        newField.at(unknownPositions.at(i)).update('*');
                        minePositions.insert(unknownPositions.at(i));
                        --valueCopy;
                        unknownPositions.erase(unknownPositions.begin() + i);
                        --i;
                        ++changes;
                        newField.foundMine();
                    }
                }
                if (valueCopy == 0 && static_cast<int>(unknownPositions.size()) > 0) {
                    //Convert all '#' around cell to 'c'
                    for (unsigned long i = 0; i < unknownPositions.size(); ++i) {
                        newField.at(unknownPositions.at(i)).update('c');
                        clickPositions.insert(unknownPositions.at(i));
                        ++changes;
                    }
                }
                if (performingDeduction == true) {
                    //The following if statements are for deductions only. This will tell the program that the current possibility being tested is incorrect.
                    if (valueCopy < 0) {
                        //cout << "Too many mines for a cell." << endl;
                        return false;
                    }
                    else if (valueCopy > static_cast<int>(unknownPositions.size())) {
                        //cout << "Not enough spaces for mines for a cell." << endl;
                        return false;
                    }
                    else if (newField.getMinesFound() > newField.getTotalMines()) {
                        cout << "Too many total mines." << endl;
                        return false;
                    }
                    else if (newField.getMinesFound() == newField.getTotalMines() && newField.needMoreMines() == true) {
                        cout << "Need more total mines" << endl;
                        return false;
                    }
                    /*
                    ** This does not work because there may be numbers that we have not uncovered
                    ** that still need more mines.
                    else if (newField.getMinesFound() < newField.getTotalMines() && newField.needMoreMines() == false) {
                        cout << "Don't need more mines, but we are not at mine total." << endl;
                        return false;
                    }
                    */

                }
            }
        }
        //cout << "Returning after " << counter << " iterations." << endl;


        return true;
    }

    Field evaluate(set<int> &clickPositions) {
        Field newField(rows, columns, cells, totalMines);
        newField.setMinesFound(minesFound);
        /*
        First, we need to map out our field. The mapping process will complete two things:
        1)  The positions of neighbor cells around all number cells that could contain mines (# or *).
        2)  The positions of neighbor cells around all number cells that are also number cells.
            Step 2 looks for neighbor cells that are numbers from the closest 2 rings
            that surround the current number cell.
        */
        newField.clearPossibleMines();
        newField.clearAdjacentNumberPositions();
        newField.mapPossibleMinesAndNumbers();

        /*
        Second, we need to identify the Strongly Connected Components (SCCs) based on our map.
        An SCC is a group of number cells that when evaluated individually can affect the way we
        evaluate the other number cells in the group. In simple terms, an SCC for our purposes is
        a chain of number cells where each number cell shares a neighbor that could contain a mine
        with at least one other number cell in the chain.
        */
        set<int> cellsVisited;
        vector<set<int>> allSCCs;
        for (int i = 0; i < newField.size(); ++i) {
            if (cellsVisited.find(i) == cellsVisited.end()) {
                //Cell has not been visited
                cellsVisited.insert(i);
                set<int> SCC;
                
                if (newField.copyAt(i).isNumber() == true) {
                    depthSearch(newField, i, cellsVisited, SCC, true);
                    SCC.insert(i);
                    allSCCs.push_back(SCC);
                }
            }
        }

        // cout << "Total number of SCCs: " << allSCCs.size() << endl;
        // for (unsigned long i = 0; i < allSCCs.size(); ++i) {
        //     cout << "SCC " << i << ":" << endl;
        //     for (auto& position: allSCCs.at(i)) {
        //         cout << position << ", ";
        //     }
        //     cout << endl << endl;
        // }

        /*
            Third, we will go through each SCC. Within each SCC, we will run a fixed-point
        algorithm that will continue to try and solve that SCC until there are no new changes
        being made.
        */
        set<int> minePositions;
        for (unsigned long i = 0; i < allSCCs.size(); ++i) {
            evaluateSCC(newField, allSCCs.at(i), clickPositions, minePositions);
        }

        return newField;
    }

    static bool advanceCombination(vector<int> &combination, int numberOfPositions) {
        //Purpose of this function is to advance the combination to the next possible combination
        bool finished = true;
        int counter = 1;
        
        for (int i = static_cast<int>(combination.size()) - 1; i >= 0; --i) {
            if (combination.at(i) != numberOfPositions - counter) {
                
                finished = false;
                break;
            }
            ++counter;
        }

        if (finished == true) {
            return true;
        }
        
        //We are not done. Update combination to the next positions
        if (combination.at(combination.size() - 1) != numberOfPositions - 1) {
            ++combination.at(combination.size() - 1);
            return false;
        }

        counter = 2;
        for (unsigned long i = combination.size() - 2; i >= 0; --i) {
            if (combination.at(i) != numberOfPositions - counter) {
                ++combination.at(i);
                for (unsigned long j = i + 1; j < combination.size(); ++j) {
                    combination.at(j) =  combination.at(j - 1) + 1;
                }
                return false;
            }
            ++counter;
        }
        return false;
    }

    static void deduceSCC(Field &newField, set<int> &SCC, set<int> &newClickPositions, bool &reevaluate) {
        for (auto& position : SCC) {
            /* Find adjacent cell possible mines for each value in the SCC */
            Cell currentCell = newField.at(position);
            char value = currentCell.getValue();
            int valueCopy = value - '0';
            vector<int> unknownPositions;
            set<int> possibleMinePositions = currentCell.getAdjacentPossibleMinePositions();
            for (auto& position2 : possibleMinePositions) {
                if (newField.copyAt(position2).getValue() == '*') {
                    --valueCopy;
                }
                else if (newField.copyAt(position2).getValue() == '#') {
                    unknownPositions.push_back(position2);
                }
            }
            /*
                Now we know how many mines we still need (valueCopy) and how many spaces are left
            in which a mine can be placed (unknownPositions.size()). 
            */
            int numberOfLoops = valueCopy;
            int numberOfPositions = static_cast<int>(unknownPositions.size());
            if (numberOfLoops > 0) {
                vector<int> combination;
                for (int i = 0; i < numberOfLoops; ++i) {
                    combination.push_back(i);
                }

                vector<vector<int>> combinationsThatWork;
                vector<set<int>> minePositionsAdded;
                vector<set<int>> clickPositionsAdded;

                //Code for first combination
                set<int> minePositions;
                set<int> clickPositions;
                Field fakeField = newField;
                for (unsigned long i = 0; i < combination.size(); ++i) {
                    fakeField.at(unknownPositions.at(combination.at(i))).update('*');
                    fakeField.foundMine();
                }
                
                bool works = evaluateSCC(fakeField, SCC, clickPositions, minePositions, true);

                if (works == true) {
                    combinationsThatWork.push_back(combination);
                    minePositionsAdded.push_back(minePositions);
                    clickPositionsAdded.push_back(clickPositions);
                }

                //Loop through the rest of possible combinations

                while (advanceCombination(combination, numberOfPositions) == false) {
                    
                    minePositions.clear();
                    clickPositions.clear();
                    fakeField = newField;
                    for (unsigned long i = 0; i < combination.size(); ++i) {
                        fakeField.at(unknownPositions.at(combination.at(i))).update('*');
                        fakeField.foundMine();
                    }
                    bool works = evaluateSCC(fakeField, SCC, clickPositions, minePositions, true);

                    if (works == true) {
                        combinationsThatWork.push_back(combination);
                        minePositionsAdded.push_back(minePositions);
                        clickPositionsAdded.push_back(clickPositions);
                    }
                }

                //If there is only one combination that worked, apply that one to the current position
                if (combinationsThatWork.size() == 1) {
                    cout << "One combo that works." << endl;
                    combination = combinationsThatWork.at(0);
                    for (unsigned long i = 0; i < combination.size(); ++i) {
                        newField.at(unknownPositions.at(combination.at(i))).update('*');
                        newField.foundMine();
                    }
                }
                /* If in every possible combination for a number, there are cells from 
                the resulting deductions that are always the same (either mine or
                empty), apply those to the field*/
                else if (combinationsThatWork.size() > 1) {
                    bool addMinePosition = true;
                    for (auto& minePosition : minePositionsAdded.at(0)) {
                        addMinePosition = true;
                        for (unsigned long i = 1; i < minePositionsAdded.size(); ++i) {
                            if (minePositionsAdded.at(i).find(minePosition) == minePositionsAdded.at(i).end()) {
                                addMinePosition = false;
                                break;
                            }
                        }
                        if (addMinePosition == true) {
                            //Add this position as a mine!
                            cout << "Found mine!" << endl;
                            newField.at(minePosition).update('*');
                            newField.foundMine();
                            reevaluate = true;
                        }
                    }

                    bool addClickPosition = true;
                    for (auto& clickPosition : clickPositionsAdded.at(0)) {
                        addClickPosition = true;
                        for (unsigned long i = 1; i < clickPositionsAdded.size(); ++i) {
                            if (clickPositionsAdded.at(i).find(clickPosition) == clickPositionsAdded.at(i).end()) {
                                addClickPosition = false;
                                break;
                            }
                        }
                        if (addClickPosition == true) {
                            //Add this position as a click!
                            cout << "Found click!" << endl;
                            newField.at(clickPosition).update('c');
                            newClickPositions.insert(clickPosition);
                        }
                    }
                }


            }
        }


        return;
    }

    Field deduction(set<int> &newClickPositions, bool &reevaluate) {
        Field newField(rows, columns, cells, totalMines);
        newField.setMinesFound(minesFound);
        newField.clearPossibleMines();
        newField.clearAdjacentNumberPositions();
        newField.mapPossibleMinesAndNumbers();

        set<int> cellsVisited;
        vector<set<int>> allSCCs;
        for (int i = 0; i < newField.size(); ++i) {
            if (cellsVisited.find(i) == cellsVisited.end()) {
                //Cell has not been visited
                cellsVisited.insert(i);
                set<int> SCC;
                
                if (newField.copyAt(i).isNumber() == true) {
                    depthSearch(newField, i, cellsVisited, SCC, true);
                    SCC.insert(i);
                    allSCCs.push_back(SCC);
                }
            }
        }
        set<int> minePositions;
        for (unsigned long i = 0; i < allSCCs.size(); ++i) {
            deduceSCC(newField, allSCCs.at(i), newClickPositions, reevaluate);
            evaluateSCC(newField, allSCCs.at(i), newClickPositions, minePositions);
        }

        return newField;
    }

};


#endif