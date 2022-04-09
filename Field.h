#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

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
    

public:
    Field (int rows, int columns, vector<char> values) {
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
    }
    Field (int rows, int columns, vector<Cell> cells) {
        this->rows = rows;
        this->columns = columns;
        this->cells = cells;
        this->top = columns * -1;
        this->bottom = columns;
    }
    Field () {
        this->rows = 0;
        this->columns = 0;
        this->top = columns * -1;
        this->bottom = columns;
    }

    int size() {
        return cells.size();
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

    void update(int rowPosition, int columnPosition, char value) {
        cells.at((rowPosition * columns) + columnPosition).update(value);
    }

    void toString() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cells.at((i * columns) + j).toString();
            }
            cout << endl;
        }
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
        cout << "In mapping" << endl;
        int currentCellPosition = 0;
        const int LEFT_EDGE = 0;
        const int RIGHT_EDGE = columns - 1;
        for (unsigned long i = 0; i < cells.size(); ++i) {
            if (cells.at(currentCellPosition).isNumber() == true) {
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
            }
            ++currentCellPosition;
        }
    }

    static void depthSearch(Field &newField, int position, set<int> &cellsVisited, set<int> &SCC, bool skipCheck = false) {
        
        if (skipCheck == true || cellsVisited.find(position) == cellsVisited.end()) {
            cellsVisited.insert(position);
            //cout << "In depth search at " << position << endl;
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

        //cout << "Returning from " << position << endl;
        return;
    }

    Field evaluate() {
        Field newField(rows, columns, cells);
        /*
            First, we need to map out the possible positions of mines for every cell.
        This will help us to determine our SCCs because we will be able to see if number cells
        share possible mine cells.
        */
        newField.clearPossibleMines();
        newField.clearAdjacentNumberPositions();
        newField.mapPossibleMinesAndNumbers();
        cout << "Mapping complete" << endl;
        int cellCounter = 0;
        for (int i = 0; i < newField.size(); ++i) {
            cout << newField.copyAt(cellCounter).getRowPosition() << " " << newField.copyAt(cellCounter).getColumnPosition() << endl;
            cout << "Cell " << cellCounter << " numbers:" << endl;
            set<int> adjacentNumbers = newField.copyAt(cellCounter).getadjacentNumberPositions();
            for (auto& adjacentNumber : adjacentNumbers) {
                cout << adjacentNumber << ", ";
            }
            cout << endl << "Cell " << cellCounter << " mines:" << endl;
            set<int> adjacentMines = newField.copyAt(cellCounter).getAdjacentPossibleMinePositions();
            for (auto& adjacentMine : adjacentMines) {
                cout << adjacentMine << ", ";
            }
            cout << endl;

            ++cellCounter;
        }

        //return newField;

        /*
            Second, we need to identify the Strongly Connected Components (SCCs). We will
        perform a depth first search for all cells with a number value. An SCC is made up of 
        cells that share neighbors that may contain a mine. Basically, this organizes the numbered cells
        into groups where every member of the group can have an effect on all other members.
        */
        set<int> cellsVisited;
        vector<set<int>> allSCCs;
        for (int i = 0; i < newField.size(); ++i) {
            if (cellsVisited.find(i) == cellsVisited.end()) {
                //Cell has not been visited
                cellsVisited.insert(i);
                //cout << "Inserting " << i << endl;
                set<int> SCC;
                
                if (newField.copyAt(i).isNumber() == true) {
                    depthSearch(newField, i, cellsVisited, SCC, true);
                    SCC.insert(i);
                    allSCCs.push_back(SCC);
                }
            }
        }

        cout << "Total number of SCCs: " << allSCCs.size() << endl;
        for (unsigned long i = 0; i < allSCCs.size(); ++i) {
            cout << "SCC " << i << ":" << endl;
            for (auto& position: allSCCs.at(i)) {
                cout << position << ", ";
            }
            cout << endl << endl;
        }

        return newField;
    }

};


#endif