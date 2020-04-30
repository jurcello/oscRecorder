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
#include <string>

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
    uint32_t minutes();
    uint32_t seconds();
    uint32_t millis();
    std::string timecode();
    
private:
    bool isRunning;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
    std::chrono::time_point<std::chrono::system_clock> mEndTime;
};
#endif /* timeline_h */