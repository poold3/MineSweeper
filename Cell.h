#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Field {
private:
    string value;
    int rowPosition;
    int columnPosition;

public:
    Cell (string value, int rowPosition, int columnPosition) {
        this.value = value;
        this.rowPosition = rowPosition;
        this.columnPosition = columnPosition;
    }

    Cell () {
        this.value = " ";
        this.rowPosition = 0;
        this.columnPosition = 0;
    }

    toString() {
        
    }


};


#endif