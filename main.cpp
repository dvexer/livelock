#include <iostream>
#include <thread>
#include <mutex>

std::mutex resourceX;
std::mutex resourceY;

void threadAFunc() {
    unsigned int workCounter = 0;
    unsigned int skipCounter = 0;

    while(true) {
        std::lock_guard<std::mutex> lockX(resourceX);
        std::this_thread::yield(); // encourage the livelock

        std::unique_lock<std::mutex> lockY(resourceY, std::defer_lock);
        if(!lockY.try_lock()) {
            ++skipCounter;
            continue;
        }

        std::cout << "threadA worked: " << ++workCounter << " skipped: " << skipCounter << "\n";
    }
}

void threadBFunc() {
    unsigned int workCounter = 0;
    unsigned int skipCounter = 0;

    while(true) {
        std::lock_guard<std::mutex> lockY(resourceY);
        std::this_thread::yield(); // encourage the livelock

        std::unique_lock<std::mutex> lockX(resourceX, std::defer_lock);

        if(!lockX.try_lock()) {
            ++skipCounter;
            continue;
        }

        std::cout << "threadB worked: " << ++workCounter << " skipped: " << skipCounter << "\n";
    }
}

int main() {
    std::thread(threadAFunc).detach();
    std::thread(threadBFunc).join();
    return 0;
}
