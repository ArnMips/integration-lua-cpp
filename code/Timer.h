#pragma once
#pragma optimize("", off) 

#include <ctime>

class Timer {
public:
    Timer();
    void start();
    void stop();
    long timeElapsed() const;
private:
    clock_t begin_;
    clock_t end_;
};

///------------------------------------------------

Timer::Timer()
    : begin_(0), end_(0)
{
}

inline void Timer::start() {
    begin_ = clock();
}

inline void Timer::stop() {
    end_ = clock();
}

inline long Timer::timeElapsed() const {
    return end_ - begin_;
}