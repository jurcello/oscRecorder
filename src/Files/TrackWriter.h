//
// Created by Jur de Vries on 25/05/2020.
//

#ifndef OSCRECORDER_TRACKWRITER_H
#define OSCRECORDER_TRACKWRITER_H


#include <memory>
#include "TrackChannel.h"
#include "ofxJSONElement.h"

class TrackWriter {

public:
    TrackWriter(OscTrackRef track);

    void write(std::string path);

private:
    OscTrackRef track;

    ofxJSONElement messageToJson(const TrackEvent<ofxOscMessage> &event) const;

    ofxJSON argsToJson(const ofxOscMessage &m) const;
};


#endif //OSCRECORDER_TRACKWRITER_H
