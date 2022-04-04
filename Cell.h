#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Cell {
private:
    string value;
    int position;

public:
    Cell (string value, int position) {
        this->value = value;
        this->position = position;
    }

    Cell () {
        this->value = " ";
        this->position = 0;
    }

    string getValue() {
        return value;
    }

    void update (string value) {
        this->value = value;
    }

    void toString() {
        cout << "[" << value << "]";
    }


};


#endif