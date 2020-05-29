//
// Created by Jur de Vries on 29/05/2020.
//

#include "MidiTimecodeSync.h"
#include "ofLog.h"


MidiTimecodeSync::MidiTimecodeSync(Timeline &timeline)
:timeline(timeline)
{
}

MidiTimecodeSyncRef MidiTimecodeSync::create(Timeline &timeline) {
    return MidiTimecodeSyncRef(new MidiTimecodeSync(timeline));
}

void MidiTimecodeSync::setup() {
    midiIn.openVirtualPort("OSC Recorder input");
    midiIn.ignoreTypes(false, // sysex  <-- don't ignore timecode messages!
            false, // timing <-- don't ignore clock messages!
            true); // sensing
    midiIn.addListener(this);
}

void MidiTimecodeSync::update() {
    if(timecodeRunning && !timecodeWasRecentlyReceived()) {
        timecodeRunning = false;
        setCurrentMillisToTimeline();
        timeline.stop();
    }
}

bool MidiTimecodeSync::timecodeWasRecentlyReceived() const {
    auto inactiveThresholdInMillis = 100;
    auto millisSinceLastReceivedTimecode = ofGetElapsedTimeMillis() - lastreceivedTimecodeMessage;
    return millisSinceLastReceivedTimecode < inactiveThresholdInMillis;
}

void MidiTimecodeSync::newMidiMessage(ofxMidiMessage &message) {
    if(timecode.update(message.bytes) && enabled) {
        timecodeUpdated = true;
        timecodeUpdateCount++;
        frame = timecode.getFrame();
        // if the last message was a timecode quarter frame message,
        // then assume the timecode master has started playback
        if(message.status == MIDI_TIME_CODE) {
            if(!timecodeRunning) {
                timecodeRunning = true;
                timeline.start();
            }
            lastreceivedTimecodeMessage = ofGetElapsedTimeMillis();
        }
        syncTimeline();

    }
}

void MidiTimecodeSync::syncTimeline() {
    if (timecodeRunning && timecodeUpdateCount > frame.rate && enabled) {
        setCurrentMillisToTimeline();
        timecodeUpdateCount = 0;
    }
}

void MidiTimecodeSync::setCurrentMillisToTimeline() const {
    auto oneHourCompensation = 3600.f;
    auto millis = static_cast<u_int64_t>((frame.toSeconds() - oneHourCompensation) * 1000.f);
    timeline.setCurrentMillis(millis);
}

void MidiTimecodeSync::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

void MidiTimecodeSync::enable() {
    enabled = true;
}

void MidiTimecodeSync::disable() {
    enabled = false;
}

