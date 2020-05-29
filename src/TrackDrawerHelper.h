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
    void setCurrentTimeMillis(uint64_t millis);
    uint64_t getMaxTimeMillis();

    int getContentSize();
    void setCurrentWindowWidth(int width);

    float calculateScrollOffsetFromTIme() const;

    void setPixelsPerSecond(float pps);

    std::vector<RulerData> getRulerData();

    int getTimeMarkerPosition() const;

    uint64_t getMillisFromPixels(float pixels);
    float getPixelsFromMillis(u_int64_t millis) const;

    bool pixelXIsVisible(int x) const;
    void setCurrentScrollOffset(int currentScrollOffset);

private:
    uint64_t maxTime;
    float pixelsPerSecond;
    uint64_t currentTimeMillis = 0;
    int currentWindowWidth = 0;

    std::string createTimecodeString(int seconds) const;

    RulerData getDataPoint(int seconds) const;

    std::string formatTimecodeString(int displaySeconds, int displayMinutes) const;

    int currentScrollOffset;
};


#endif //OSCRECORDER_TRACKDRAWERHELPER_H
