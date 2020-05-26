//
// Created by Jur de Vries on 25/05/2020.
//

#ifndef OSCRECORDER_TRACKWRITERREADER_H
#define OSCRECORDER_TRACKWRITERREADER_H


#include <memory>
#include "TrackChannel.h"
#include "ofxJSONElement.h"

class TrackWriterReader {

public:
    TrackWriterReader(OscTrackRef track);

    void write(std::string path);
    void readFromFile(std::string path);

private:
    OscTrackRef track;
    OscTrackRecorderRef recorder;

    void emptyTrack() const;

    ofxJSONElement messageToJson(const TrackEvent<ofxOscMessage> &event) const;
    ofxJSON argsToJson(const ofxOscMessage &m) const;

    ofxOscMessage jsonToOscMessage(const ofxJSON &messageJson);
    void jsonArgsToOscMessage(ofxOscMessage &m, const Json::Value &jsonArgs) const;
};


#endif //OSCRECORDER_TRACKWRITERREADER_H
