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

public:
    Field (int rows, int columns, vector<char> values) {
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i < rows * columns; ++i) {
            Cell cell(values.at(i), i);
            cells.push_back(cell);
        }
    }
    Field (int rows, int columns, vector<Cell> cells) {
        this->rows = rows;
        this->columns = columns;
        this->cells = cells;
    }
    Field () {
        this->rows = 0;
        this->columns = 0;
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

    Field evaluate() {
        Field newField(rows, columns, cells);
        /*
            First, we need to identify the Strongly Connected Components (SCCs). We will
        perform a depth first search for all cells with a number value. An SCC is made up of 
        cells that are within 2 cells of each other. Basically, this organizes the numbered cells
        into groups where every member of the group can have an effect on all other members.
        
            We will run a fixed-point algorithm on each SCC until there are no new changes
        being made.
        */
        Set<int> cellsVisited;
        for (int i = 0; i < newField.size(); ++i) {

        }

        return newField;
    }

};


#endif