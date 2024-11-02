#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
    last = std::chrono::steady_clock::now();
}

float FrameTimer::frame()
{
    const auto old = last;
    last = std::chrono::steady_clock::now(); // update the timestamp
    const std::chrono::duration<float> frameTime = old - last; // how long since last frame
    return frameTime.count();
}