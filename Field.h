#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

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
    vector<int> adjacentNumberPositionIncrements;
    vector<int> adjacentMinePositionIncrements;

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
        this->adjacentNumberPositionIncrements = {2*top + 2*left, 2*top + left, 2*top, 2*top + right, 
            2*top + 2*right, top + 2*left, top + left, top, top + right, top + 2*right, 2*left, 
            left, right, 2*right, bottom + 2*left, bottom + left, bottom, bottom + right, 
            bottom + 2*right, 2*bottom + 2*left, 2*bottom + left, 2*bottom, 2*bottom + right, 
            2*bottom + 2*right};
        this->adjacentMinePositionIncrements = {top + left, top, top + right, left, right, 
            bottom + left, bottom, bottom + right};
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

    static void evaluateSCC(Field &newField, set<int> &SCC) {
        // cout << "SCC Evaluation" << endl;
        // for (auto& position: SCC) {
        //     cout << position << ", ";
        // }
        //cout << endl << endl;
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
                    if (newField.copyAt(position2).getValue() == 'f') {
                        --valueCopy;
                    }
                    else if (newField.copyAt(position2).getValue() == '*') {
                        unknownPositions.push_back(position2);
                    }
                }
                if (valueCopy > 0 && valueCopy == static_cast<int>(unknownPositions.size())) {
                    //Convert all '*' around cell to 'f'
                    for (unsigned long i = 0; i < unknownPositions.size(); ++i) {
                        newField.at(unknownPositions.at(i)).update('f');
                        --valueCopy;
                        unknownPositions.erase(unknownPositions.begin() + i);
                        --i;
                        ++changes;
                    }
                }
                if (valueCopy == 0 && static_cast<int>(unknownPositions.size()) > 0) {
                    //Convert all '*' around cell to 'c'
                    for (unsigned long i = 0; i < unknownPositions.size(); ++i) {
                        newField.at(unknownPositions.at(i)).update('c');
                        ++changes;
                    }
                }
            }
            if (counter == 1000) {
                break;
            }
        }
        cout << "Returning after " << counter << " iterations." << endl;


        return;
    }

    Field evaluate() {
        Field newField(rows, columns, cells);
        /*
            First, we need to map out our field. The mapping process will complete two things:
                1)  The positions of neighbor cells around all number cells that could contain mines.
                2)  The positions of neighbor cells around all number cells that are also number cells.
                    Step 2 looks for neighbor cells that are numbers from the closest 2 rings
                    that surround the current number cell.
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

        cout << "Total number of SCCs: " << allSCCs.size() << endl;
        for (unsigned long i = 0; i < allSCCs.size(); ++i) {
            cout << "SCC " << i << ":" << endl;
            for (auto& position: allSCCs.at(i)) {
                cout << position << ", ";
            }
            cout << endl << endl;
        }

        /*
            Third, we will go through each SCC. Within each SCC, we will run a fixed-point
        algorithm that will continue to try and solve that SCC until there are no new changes
        being made.
        */

        for (unsigned long i = 0; i < allSCCs.size(); ++i) {
            evaluateSCC(newField, allSCCs.at(i));
        }


        return newField;
    }

};


#endif