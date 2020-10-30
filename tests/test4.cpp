#include <thread>
#include <iostream>
#include <unistd.h>

void loop1() {
    while (1) {
        std::string buffer;
        std::cin >> buffer;
        std::cout << buffer << std::endl;
    }
}

void loop2() {
    while (1) {
        std::cout << "." << std::endl;
        usleep(100000);
    }
}

int main()
{
    //std::atomic<bool> run(true);
    std::thread thread1(loop1);
    std::thread thread2(loop2);

    thread1.join(); // pauses until first finishes
    thread2.join(); // pauses until second finishes

    return 0;
}