#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Scanner {
private:
    const string inputFile;
    queue<char> tokens;
    int rows = 0;
    int columns = 0;
public:
    Scanner(const string inputFile) : inputFile(inputFile){}

    queue<char> getTokens() {
        return tokens;
    }

    int getRows() {
        return rows;
    }

    int getColumns() {
        return columns;
    }

    void scanField() {
        int countRows = 0;
        int countCells = 0;
        ifstream infile;
        string inputLine;
        infile.open(inputFile);
        if (infile.is_open()) {
            while(getline(infile, inputLine)) {
                while(inputLine.length() > 0) {
                    if (inputLine.at(0) == '[') {
                        tokens.push('[');
                        ++countCells;
                    }
                    else if (inputLine.at(0) == ']') {
                        tokens.push(']');
                    }
                    else if (inputLine.at(0) == 'f') {
                        tokens.push('f');
                    }
                    else if (inputLine.at(0) == ' ') {
                        tokens.push(' ');
                    }
                    else if (inputLine.at(0) == '*') {
                        tokens.push('*');
                    }
                    else if (isdigit(inputLine.at(0)) && inputLine.at(0)-48 > 0 && inputLine.at(0)-48 < 9) {
                        tokens.push(inputLine.at(0));
                    }
                    else {
                        string error = "Invalid character detected: ";
                        error += inputLine.at(0);
                        throw std::invalid_argument(error);
                    }
                    inputLine = inputLine.substr(1);
                }
                ++countRows;
            }
            rows = countRows;
            columns = countCells / countRows;
        }
        infile.close();
        return;
    }

};

#endif