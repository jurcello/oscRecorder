//
// Created by Jur de Vries on 16/04/2020.
//

#ifndef OSCRECORDER_TIMELINEUI_H
#define OSCRECORDER_TIMELINEUI_H

#include <memory>
#include "timeline.h"
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxImGui.h"
#include "Utils.h"

class TimelineUI;

typedef std::shared_ptr<TimelineUI> TimelineUIRef;

class TimelineUI {
public:
    static TimelineUIRef create(Timeline &timeline, bool &recording);
    void drawUi();
    void setInputMessage(ofxOscMessage message);

private:
    TimelineUI(Timeline &timeline, bool &recording);

    Timeline &timeline;
    bool &recording;
    ofxOscMessage inputMessage;
};


#endif //OSCRECORDER_TIMELINEUI_H