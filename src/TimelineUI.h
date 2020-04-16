//
// Created by Jur de Vries on 16/04/2020.
//

#ifndef OSCRECORDER_TIMELINEUI_H
#define OSCRECORDER_TIMELINEUI_H

#include <memory>
#include "timeline.h"
#include "ofMain.h"
#include "ofxImGui.h"

class TimelineUI;

typedef std::shared_ptr<TimelineUI> TimelineUIRef;

class TimelineUI {
public:
    static TimelineUIRef create(Timeline &timeline, bool &recording);
    void drawUi();

private:
    TimelineUI(Timeline &timeline, bool &recording);

    Timeline &timeline;
    bool &recording;
};


#endif //OSCRECORDER_TIMELINEUI_H
