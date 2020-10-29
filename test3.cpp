#include <atomic>
#include <thread>
#include <iostream>
#include <unistd.h>

void ReadCin(std::atomic<bool>& run)
{
    std::string buffer;
    while (run.load()) {
        std::cin >> buffer;
        if (buffer == "Quit")
            run.store(false);
    }
}

int main()
{
    std::atomic<bool> run(true);
    std::thread cinThread(ReadCin, std::ref(run));

    while (run.load()) {
        // main loop
        usleep(100000);
        std::cout << "." << std::endl;
    }

    run.store(false);
    cinThread.join();

    return 0;
}