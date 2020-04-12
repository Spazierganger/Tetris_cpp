//
// Created by chendi on 2020/4/11.
//

#include <iostream>
#include <thread>

void independentThread()
{
    for(int i=0; i < 100; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Hello.\n";
    }
}

void threadCaller()
{
    std::thread t(independentThread);
//    t.join();
    t.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for(int j = 0; j < 1000; j++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Exiting thread caller.\n";
    }
}

int main()
{
    threadCaller();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "End.\n";
    return 0;
}