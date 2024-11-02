#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include <chrono>

class FrameTimer
{
public:
    FrameTimer();
    float frame();

public:
    std::chrono::steady_clock::time_point last; // last frame mark
};

#endif