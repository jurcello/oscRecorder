//
//  timeline.cpp
//  oscRecorder
//
//  Created by Jur de Vries on 04/04/2020.
//

#include "timeline.h"

Timeline::Timeline()
:isRunning(false)
{
    reset();
}

bool Timeline::running() {
    return isRunning;
}

void Timeline::reset() {
    mStartTime = std::chrono::system_clock::now();
    mEndTime = mStartTime;
}

void Timeline::start() {
    if (mEndTime > mStartTime) {
        // Shift the startTime.
        auto now = std::chrono::system_clock::now();
        auto timeDifference = now - mEndTime;
        mEndTime = now;
        mStartTime += timeDifference;
    }
    else {
        reset();
    }
    isRunning = true;
}

void Timeline::stop() {
    mEndTime = std::chrono::system_clock::now();
    isRunning = false;
}

void Timeline::startStop() {
    if (isRunning) {
        stop();
        return;
    }
    start();
}

uint64_t Timeline::elapsedMillis() {
    std::chrono::time_point<std::chrono::system_clock> endTime;
    
    if (isRunning) {
        endTime = std::chrono::system_clock::now();
    }
    else {
        endTime = mEndTime;
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - mStartTime).count();
}

double Timeline::elapsedSeconds() {
    return elapsedMillis() / 1000.f;
}
