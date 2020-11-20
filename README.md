# ArduinoSimulator
Simulates the serial communication between two Arduinos on the command line.
Multiple encryption methods for the communication can be tried out.

## Prerquisites
You only need the gnu C++ compiler without any additional libraries.

## Compiling
Type
```
g++ Caesar.cpp -std=c++17 -pthread -o comm
```
to compile the code.

## Usage
Since the simulated serial communication is based on named pipes, you have to create them first:
```
mkfifo stdout12
mkfifo stdout21
mkfifo stdout23
mkfifo stdout32
mkfifo stdout13
mkfifo stdout31
```

Afterwards, open three terminal windows and start three seperate "Arduino" instances
```
./comm -a
./comm -b
./comm -c
```
Arduinos `a` (Alice) and `b` (Bob) can communicate with each other by submitting text into the corresponding terminal windows. 
Arduino `c` (Carter) is in a man-in-the-middle (MiTM) position and tries to eavesdrop on the communication.
