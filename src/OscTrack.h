//
// Created by Jur de Vries on 09/04/2020.
//

#ifndef OSCRECORDER_OSCTRACK_H
#define OSCRECORDER_OSCTRACK_H

#include "ofxOsc.h"

struct OscEvent {

    uint64_t millis;
    ofxOscMessage event;
};

class OscTrack {

};


#endif //OSCRECORDER_OSCTRACK_H
