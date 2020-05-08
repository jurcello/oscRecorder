//
// Created by Jur de Vries on 30/04/2020.
//

#include "TrackDrawerHelper.h"

void TrackDrawerHelper::setMaxTimeMillis(uint64_t millis) {
    maxTime = millis;
}

uint64_t TrackDrawerHelper::getMaxTimeMillis() {
    return maxTime;
}

int TrackDrawerHelper::getContentSize() {
    return static_cast<int>(pixelsPerSecond * (maxTime / 1000));
}

void TrackDrawerHelper::setPixelsPerSecond(float pps) {
    pixelsPerSecond = pps;
}

std::vector<RulerData> TrackDrawerHelper::getRulerData() {
    auto rulerData = std::vector<RulerData>();
    auto seconds = 0;
    while (seconds * 1000.f <= getMaxTimeMillis()) {
        RulerData dataPoint = getDataPoint(seconds);
        rulerData.push_back(dataPoint);
        seconds += 1;
    }
    return rulerData;
}

RulerData TrackDrawerHelper::getDataPoint(int seconds) const {
    auto pixelPosition = calculatePixelPosition(seconds);
    auto dataPoint = RulerData(static_cast<int>(pixelPosition), "");
    if (seconds % 5 == 0) {
        std::string secondsText = createTimecodeString(seconds);
        dataPoint.text = secondsText;
        dataPoint.hasText = true;
    }
    return dataPoint;
}

float TrackDrawerHelper::calculatePixelPosition(int seconds) const {
    return seconds * pixelsPerSecond;
}

std::string TrackDrawerHelper::createTimecodeString(int seconds) const {
    auto displaySeconds = seconds % 60;
    auto displayMinutes = seconds / 60;
    std::string secondsText = formatTimecodeString(displaySeconds, displayMinutes);
    return secondsText;
}

std::string TrackDrawerHelper::formatTimecodeString(int displaySeconds, int displayMinutes) const {
    char timeCode[5];
    sprintf(timeCode, "%.2d:%.2d", displayMinutes, displaySeconds);
    std::string secondsText = timeCode;
    return secondsText;
}
