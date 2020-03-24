//
// Created by chendi on 2020/3/23.
//
// a simple trial with timer. but only a timer, no function as multi thread.

#include <iostream>
#include <chrono>

using namespace std;

class Timer
{
private:
    chrono::time_point<chrono::steady_clock> s_time;
    chrono::time_point<chrono::steady_clock> e_time;
    chrono::time_point<chrono::steady_clock> r_time;
    bool running = false;

public:
    void start_timer()
    {
        this->running = true;
        this->s_time = chrono::steady_clock::now();
    }

    void stop_timer()
    {
        this->running = false;
        this->e_time = chrono::steady_clock::now();
    }

    bool time_out(int interval)
    {
        if(this->running)
            r_time = chrono::steady_clock::now();
        else
            r_time = e_time;

        auto duration = chrono::duration_cast<std::chrono::milliseconds>(r_time - s_time).count();
        if(duration > interval)
        {
            this->stop_timer();
            return true;
        }
        else
            return false;
    }

};

int main()
{
    Timer t1;
    t1.start_timer();
    int count = 0;
    while(!t1.time_out(5000))
    {
        count += 1;
    }
    cout << "Time out!" << endl;
    return 0;
}