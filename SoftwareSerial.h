#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Globals.h"

// class to emulate the serial communication between
// the participants
class SoftwareSerial {
public:
    // dummy constructor
    SoftwareSerial(int, int) {}

    // dummy function
    void begin(int) {}

    bool available() {
        const size_t size = Globals::s_pipeBuffer.size();
        if (size >= 2) {
            bool t1 = Globals::s_pipeBuffer[size - 1] == '\1'; // last character
            char t2 = Globals::s_pipeBuffer[size - 2] == '\1';
            // buffer ends with termination characters
            if (t1 && t2) {
                Globals::s_pipeBuffer.erase(Globals::s_pipeBuffer.end() - 1);
                Globals::s_pipeBuffer.erase(Globals::s_pipeBuffer.end() - 1);
                //std::cout << Globals::s_pipeBuffer;
                return true;
            }
        }
        return false;
    }

    char read() {
        char c = 0;
        if (Globals::s_pipeBuffer.size() > 0) {
            c = Globals::s_pipeBuffer[0];
            Globals::s_pipeBuffer.erase(Globals::s_pipeBuffer.begin());
        }
        return c;
    }

    std::string readString() {
        //usleep(10000);
        std::string buffer = Globals::s_pipeBuffer;
        Globals::s_pipeBuffer = std::string();
        return buffer;
    }

    void print(char c) {
        std::string filename(Globals::s_arduino->writeTo());
        const size_t size = sizeof(c);
        std::ofstream pipe(filename, std::ios::out | std::ios::binary);
        pipe.write(&c, size);
        usleep(1000);
        pipe.close();
    }

    void print(const std::string& str) {
        for(const char& c : str) {
            print(c);
        }
        // terminate
        print('\1');
        print('\1');
    }

    void write(char c) {
        print(c);
        // terminate
        print('\1');
        print('\1');
    }
};