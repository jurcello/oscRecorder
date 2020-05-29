//
// Created by Jur de Vries on 29/05/2020.
//

#ifndef OSCRECORDER_MIDITIMECODESYNC_H
#define OSCRECORDER_MIDITIMECODESYNC_H

#include "ofxMidi.h"
#include "timeline.h"
#include "ofUtils.h"

class MidiTimecodeSync;

typedef std::shared_ptr<MidiTimecodeSync> MidiTimecodeSyncRef;

class MidiTimecodeSync: public ofxMidiListener {
public:
    static MidiTimecodeSyncRef create(Timeline &timeline);
    void setup();
    void update();
    void newMidiMessage(ofxMidiMessage &message);
    void enable();
    void disable();
    void exit();
private:
    MidiTimecodeSync(Timeline &timeline);

    ofxMidiIn midiIn;
    Timeline &timeline;

    ofxMidiTimecode timecode; //< timecode message parser
    bool timecodeUpdated = false;
    int timecodeUpdateCount = 0;
    bool timecodeRunning = false; //< is the timecode sync running?
    long lastreceivedTimecodeMessage = 0; //< when last quarter frame message was received
    ofxMidiTimecodeFrame frame; //< timecode frame data, ie. H M S frame rate
    bool enabled = false;

    bool timecodeWasRecentlyReceived() const;
    void setCurrentMillisToTimeline() const;
    void syncTimeline();
};


#endif //OSCRECORDER_MIDITIMECODESYNC_H
