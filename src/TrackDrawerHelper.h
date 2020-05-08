//
// Created by Jur de Vries on 30/04/2020.
//

#ifndef OSCRECORDER_TRACKDRAWERHELPER_H
#define OSCRECORDER_TRACKDRAWERHELPER_H

#include <cstdint>
#include <experimental/vector>
#include "RulerData.h"

class TrackDrawerHelper {
public:
    void setMaxTimeMillis(uint64_t millis);

    uint64_t getMaxTimeMillis();

    int getContentSize();

    void setPixelsPerSecond(float pps);

    std::vector<RulerData> getRulerData();

private:
    uint64_t maxTime;
    float pixelsPerSecond;

    std::string createTimecodeString(int seconds) const;

    float calculatePixelPosition(int seconds) const;

    RulerData getDataPoint(int seconds) const;

    std::string formatTimecodeString(int displaySeconds, int displayMinutes) const;
};


#endif //OSCRECORDER_TRACKDRAWERHELPER_H
