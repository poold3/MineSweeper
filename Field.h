#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Cell.h"

using namespace std;

class Field {
private:
    vector<Cell> cells;
    int rows;
    int columns;

public:
    Field (int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i < rows * columns; ++i) {
            Cell cell(" ", i);
            cells.push_back(cell);
        }
    }
    Field () {
        this->rows = 0;
        this->columns = 0;
    }

    Cell at(int rowPosition, int columnPosition) {
        return cells.at((rowPosition * columns) + columnPosition);
    }

    void update(int rowPosition, int columnPosition, string value) {
        cells.at((rowPosition * columns) + columnPosition).update(value);
    }

    void toString() {
        cout << "Current Field" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cells.at((i * columns) + j).toString();
                cout << " ";
            }
            cout << endl;
        }
    }


};


#endif