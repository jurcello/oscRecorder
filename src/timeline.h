//
//  timeline.hpp
//  oscRecorder
//
//  Created by Jur de Vries on 04/04/2020.
//

#ifndef timeline_h
#define timeline_h

#include <stdio.h>
#include <chrono>
#include <ctime>

#endif /* timeline_h */

class Timeline {
public:
    Timeline();
    void start();
    void stop();
    void startStop();
    bool running();
    void reset();
    uint64_t elapsedMillis();
    double elapsedSeconds();
    
    
private:
    bool isRunning;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
    std::chrono::time_point<std::chrono::system_clock> mEndTime;
};
