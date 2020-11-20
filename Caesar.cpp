// Program to simulate the serial (encrypted) communication between multiple Arduinos
// compile: g++ Caesar.cpp -std=c++17 -pthread -o comm
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

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <thread>
#include "CommandLineParser.h"

class Arduino {
public:
    //virtual ~Arduino() = 0;
    virtual void begin() = 0;
    virtual void loop() = 0;
    virtual std::string writeTo() = 0;
    virtual std::string readFrom() = 0;
};

// globals
// surely not the best way to do it, but it works
std::string s_cinBuffer;
std::string s_pipeBuffer;
Arduino* s_arduino;
//typedef std::string String;

class String : public std::string {
public:
    using std::string::string;
};

// class which handles writing from the named pipes
// in two seperate threads.
class IOHandler {
public:
    void cinThread() {
        while (1) {
            std::string buffer;
            getline(std::cin, buffer);
            buffer += '\n';
            s_cinBuffer = buffer;
        }
    }

    void pipeThread() {
        while(1) {
            char c = 0;
            std::string filename(s_arduino->readFrom());
            const size_t size = sizeof(c);
            std::ifstream pipe(filename, std::ios::in | std::ios::binary);
            pipe.read(&c, size);
            pipe.close();
            s_pipeBuffer += c;
        }
    }
};

// class to emulate the serial communication between
// the participants
class SoftwareSerial {
public:
    // dummy constructor
    SoftwareSerial(int, int) {}

    // dummy function
    void begin(int) {}

    bool available() {
        return (s_pipeBuffer.size() > 0);
    }

    char read() {
        char c = 0;
        if (s_pipeBuffer.size() > 0) {
            c = s_pipeBuffer[0];
            s_pipeBuffer.erase(s_pipeBuffer.begin());
        }
        return c;
    }

    std::string readString() {
        std::string buffer = s_pipeBuffer;
        s_pipeBuffer = std::string();
        return buffer;
    }

    void write(char c) {
        std::string filename(s_arduino->writeTo());
        const size_t size = sizeof(c);
        std::ofstream pipe(filename, std::ios::out | std::ios::binary);
        pipe.write(&c, size);
        usleep(1000);
        pipe.close();
    }

    void print(std::string str) {
        for(char& c : str) {
            write(c);
        }
    }
};

// "serial" communication with the command line
// read and print characters from/to command line
class Serial_ {
public:
    // dummy function
    void begin(int) {}

    bool available() {
        return (s_cinBuffer.size() > 0);
    }

    char read() {
        char c = 0;
        if (s_cinBuffer.size() > 0) {
            c = s_cinBuffer[0];
            s_cinBuffer.erase(s_cinBuffer.begin());
        }
        return c;
    }

    std::string readString() {
        std::string buffer = s_cinBuffer;
        s_cinBuffer = std::string();
        return buffer;
    }

    void write(char c) {
        std::cout << c;
    }

    void print(std::string str) {
        std::cout << str;
    }
} Serial;

// first participant (Alice)
class Alice : public Arduino {
public:

    // ########### CODE BLOCK BEGIN ###########
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    String encrypt(String clr, int key) {
        String cphr;
        for (int i = 0; i < clr.size(); i++) {
            // einzelnen Buchstaben aus dem Klartext im Alphabet verschieben -> "Verschlüsselung"
            char temp = clr[i] - key;
            // verschlüsselten Buchstaben temp an Cipher-Text cphr anhängen
            cphr = cphr + temp;
        }
        return cphr;
    }

    String decrypt(String cphr, int key) {
        String clr;
        for (int i = 0; i < cphr.size(); i++) {
            // einzelnen Buchstaben aus dem Cipher-Text im Alphabet verschieben -> "Entschlüsselung"
            char temp = cphr[i] + key;
            // entschlüsselten Buchstaben temp an Klartext clr anhängen
            clr = clr + temp;
        }
        return clr;
    }

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        int key = 1;

        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (Serial.available()) {
            String clr = Serial.readString();
            String cphr = encrypt(clr, key);
            mySerial.print(cphr);
        }

        // receive the characters from mySerial (named pipe) and write to Serial (console)
        if (mySerial.available()) {
            String cphr = mySerial.readString();
            String clr = decrypt(cphr, key);
            Serial.print(clr);
        }

        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    Alice() {}
    ~Alice() {}
    std::string writeTo() {return "stdout12";}
    std::string readFrom() {return "stdout21";}
};

// second participant (Bob)
class Bob : public Arduino {
public:

    // ########### CODE BLOCK BEGIN ###########
    // Arduino-like program
    SoftwareSerial mySerial  = SoftwareSerial(2, 3);

    String encrypt(String clr, int key) {
        String cphr;
        for (int i = 0; i < clr.size(); i++) {
            // einzelnen Buchstaben aus dem Klartext im Alphabet verschieben -> "Verschlüsselung"
            char temp = clr[i] - key;
            // verschlüsselten Buchstaben temp an Cipher-Text cphr anhängen
            cphr = cphr + temp;
        }
        return cphr;
    }

    String decrypt(String cphr, int key) {
        String clr;
        for (int i = 0; i < cphr.size(); i++) {
            // einzelnen Buchstaben aus dem Cipher-Text im Alphabet verschieben -> "Entschlüsselung"
            char temp = cphr[i] + key;
            // entschlüsselten Buchstaben temp an Klartext clr anhängen
            clr = clr + temp;
        }
        return clr;
    }

    void begin() {
        Serial.begin(115200);
        mySerial.begin(74880);
    }

    void loop() {
        int key = 1;

        // receive the characters from Serial (console) and write to mySerial (named pipe)
        if (Serial.available()) {
            String clr = Serial.readString();
            String cphr = encrypt(clr, key);
            mySerial.print(cphr);
        }

        // receive the characters from mySerial (named pipe) and write to Serial (console)
        if (mySerial.available()) {
            String cphr = mySerial.readString();
            String clr = decrypt(cphr, key);
            Serial.print(clr);
        }

        usleep(10);
    }
    // ########### CODE BLOCK END #############

public:
    Bob() {}
    ~Bob() {}
    std::string writeTo() {return "stdout21";}
    std::string readFrom() {return "stdout12";}
};

// program logic
int main(int argc, char* args[]) {
    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-a")) {
        s_arduino = new Alice;
    }

    if (auxiliary::CommandLineParser::cmdOptionExists(args, args + argc, "-b")) {
        s_arduino = new Bob;
    }

    IOHandler iohandler;
    std::thread thread1(&IOHandler::cinThread, iohandler);
    std::thread thread2(&IOHandler::pipeThread, iohandler);
    s_arduino->begin();
    while(1) {
        s_arduino->loop();
    }

    // is never reached
    thread1.join();
    thread2.join();
    //delete s_arduino;
}
