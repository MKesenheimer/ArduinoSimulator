#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Globals.h"

// class which handles writing from the named pipes
// in two seperate threads.
class IOHandler {
public:
    void cinThread() {
        while (1) {
            std::string buffer;
            getline(std::cin, buffer);
            buffer += '\n';
            Globals::s_cinBuffer = buffer;
        }
    }

    void pipeThread() {
        while(1) {
            char c = 0;
            std::string filename(Globals::s_arduino->readFrom());
            const size_t size = sizeof(c);
            std::ifstream pipe(filename, std::ios::in | std::ios::binary);
            pipe.read(&c, size);
            pipe.close();
            Globals::s_pipeBuffer += c;
        }
    }
};