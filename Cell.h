#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Cell {
private:
    char value;
    int position;
    int rowPosition;
    int columnPosition;
    set<int> adjacentPossibleMinePositions;
    set<int> adjacentNumberPositions;
public:
    Cell (char value, int position, int rowPosition, int columnPosition) {
        this->value = value;
        this->position = position;
        this->rowPosition = rowPosition;
        this->columnPosition = columnPosition;
    }

    Cell () {
        this->value = ' ';
        this->position = 0;
        this->rowPosition = 0;
        this->columnPosition = 0;
    }

    int getRowPosition() {
        return rowPosition;
    }

    int getColumnPosition() {
        return columnPosition;
    }

    bool isNumber() {
        if (isdigit(value)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool possibleMine() {
        //if (value != ' ' && isdigit(value) == false) {
        if (value == '*' || value == 'f') {
            return true;
        }
        else {
            return false;
        }
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

    string returnString() {
        string stringValue = "[";
        stringValue += value;
        stringValue += "]";
        return stringValue;
    }

    void addAdjacentPossibleMinePosition(int position) {
        adjacentPossibleMinePositions.insert(position);
    }

    set<int> getAdjacentPossibleMinePositions() {
        return adjacentPossibleMinePositions;
    }

    void clearPossibleMines() {
        adjacentPossibleMinePositions.clear();
    }

    void addAdjacentNumberPosition(int position) {
        adjacentNumberPositions.insert(position);
    }

    set<int> getadjacentNumberPositions() {
        return adjacentNumberPositions;
    }

    void clearAdjacentNumberPositions() {
        adjacentNumberPositions.clear();
    }


};


#endif