//
// Created by Jur de Vries on 14/04/2020.
//

#ifndef OSCRECORDER_TRACKCHANNEL_H
#define OSCRECORDER_TRACKCHANNEL_H

#include "ofxOsc.h"
#include "Track.h"
#include "TrackRecorder.h"
#include "TrackPlayer.h"

typedef Track<ofxOscMessage> OscTrack;
typedef TrackPlayer<ofxOscMessage> OscTrackPlayer;
typedef TrackRecorder<ofxOscMessage> OscTrackRecorder;
typedef std::shared_ptr<OscTrack> OscTrackRef;
typedef std::shared_ptr<OscTrackPlayer> OscTrackPlayerRef;
typedef std::shared_ptr<OscTrackRecorder> OscTrackRecorderRef;

class TrackChannel {
public:
    TrackChannel();
    OscTrackPlayerRef player;
    OscTrackRecorderRef recorder;
    OscTrackRef track;
};


#endif //OSCRECORDER_TRACKCHANNEL_H
