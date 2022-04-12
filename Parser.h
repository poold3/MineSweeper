#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Parser {
private:
    queue<char> tokens;
    vector<char> fieldValues;
public:
    Parser(queue<char> tokens) : tokens(tokens){}

    vector<char> getValues() {
        return fieldValues;
    }

    void Error(string message) {
        string error = message;
        error += tokens.front();
        throw std::invalid_argument(error);
    }

    void match(char token) {
        if (tokens.front() == token) {
            tokens.pop();
        }
        else {
            Error("Invalid order detected: ");
        }

        return;
    }

    void matchNumber() {
        if (isdigit(tokens.front())) {
            tokens.pop();
        }
        else {
            Error("Invalid order detected: ");
        }
        return;
    }
    
    void scanTokens() {
        while(tokens.size() > 0) {
            match('[');
            if (tokens.front() == ' ') {
                fieldValues.push_back(tokens.front());
                match(' ');
            }
            else if (tokens.front() == '*') {
                fieldValues.push_back(tokens.front());
                match('*');
            }
            else if (tokens.front() == '#') {
                fieldValues.push_back(tokens.front());
                match('#');
            }
            else if (isdigit(tokens.front())) {
                fieldValues.push_back(tokens.front());
                matchNumber();
            }
            else {
                string error = "Invalid order detected: ";
                error += tokens.front();
                throw std::invalid_argument(error);
            }
            match(']');
        }


        return;
    }


};

#endif