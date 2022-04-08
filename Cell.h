#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Cell {
private:
    char value;
    int position;

public:
    Cell (char value, int position) {
        this->value = value;
        this->position = position;
    }

    Cell () {
        this->value = ' ';
        this->position = 0;
    }

    char getValue() {
        return value;
    }

    void update (char newValue) {
        value = newValue;
    }

    void toString() {
        cout << "[" << value << "]";
    }


};


#endif