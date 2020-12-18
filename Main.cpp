// Program to simulate the serial (encrypted) communication between multiple Arduinos
// compile: g++ Main.cpp -std=c++17 -pthread -o comm
// To emulate the (serial) communication between the arduinos,
// these programs use named pipes. You have to generate the named pipes
// before starting the programs.
// mkfifo stdout12
// mkfifo stdout21
// mkfifo stdout23
// mkfifo stdout32
// mkfifo stdout13
// mkfifo stdout31
// Then start the three instances of the arduinos in three seperate terminal
// windows (Alice, Bob, Carter).
// Alice and Bob speek two each other, whereas Carter is in a man in the middle
// position and tries to eavesdrop on the communication.
// ./comm -a
// ./comm -b
// ./comm -c

#include <thread>
#include "typedefs.h"
#include "CommandLineParser.h"
#include "Arduino.h"
#include "Globals.h"
#include "IOHandler.h"
#include "Alice.h"
#include "Bob.h"

std::string Globals::s_cinBuffer;
std::string Globals::s_pipeBuffer;
ArduinoC* Globals::s_arduino;

// program logic
int main(int argc, char* args[]) {
    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-a")) {
        Globals::s_arduino = new Alice;
    } else if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-b")) {
        Globals::s_arduino = new Bob;
    } else {
        std::cout << "Error: use arguments -a or -b." << std::endl;
        return -1;
    }

    IOHandler iohandler;
    std::thread thread1(&IOHandler::cinThread, iohandler);
    std::thread thread2(&IOHandler::pipeThread, iohandler);
    Globals::s_arduino->setup();
    while(1) {
        Globals::s_arduino->loop();
    }

    // is never reached
    thread1.join();
    thread2.join();
    //delete s_arduino;

    return 0;
}
