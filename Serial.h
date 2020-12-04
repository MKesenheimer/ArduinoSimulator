#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Globals.h"

// "serial" communication with the command line
// read and print characters from/to command line
class Serial_ {
public:
    // dummy function
    void begin(int) {}

    bool available() {
        return (Globals::s_cinBuffer.size() > 0);
    }

    char read() {
        char c = 0;
        if (Globals::s_cinBuffer.size() > 0) {
            c = Globals::s_cinBuffer[0];
            Globals::s_cinBuffer.erase(Globals::s_cinBuffer.begin());
        }
        return c;
    }

    std::string readString() {
        std::string buffer = Globals::s_cinBuffer;
        Globals::s_cinBuffer = std::string();
        return buffer;
    }

    void write(char c) {
        std::cout << c;
    }

    void print(std::string str) {
        std::cout << str;
    }
} Serial;