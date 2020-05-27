#pragma once

#include "ofMain.h"
#include "timeline.h"
#include "ofxOsc.h"
#include "TrackChannel.h"
#include "ofxImGui.h"
#include "TimelineUI.h"
#include "TracksWindowUI.h"
#include "ofxMidi.h"

#define IN_PORT 9900
#define OUT_PORT 1100

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
		void drawUI();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void exit() override;

    void newMidiMessage(ofxMidiMessage &message) override;

private:
    Timeline timeline;
    ofxOscReceiver receiver;
    ofxOscSender sender;
    bool recording;
    TrackChannel trackChannel;
    ofxOscMessage lastMessage;

    TimelineUIRef timelineUI;
    TracksWindowUI tracksUI;
    ofxImGui::Gui gui;

    ofxMidiIn midiIn;

    // MIDI CLOCK

    ofxMidiClock clock; //< clock message parser
    bool clockRunning = false; //< is the clock sync running?
    unsigned int beats = 0; //< song pos in beats
    double seconds = 0; //< song pos in seconds, computed from beats
    double bpm = 120; //< song tempo in bpm, computed from clock length
    // MIDI TIMECODE

    ofxMidiTimecode timecode; //< timecode message parser
    bool timecodeRunning = false; //< is the timecode sync running?
    long timecodeTimestamp = 0; //< when last quarter frame message was received
    ofxMidiTimecodeFrame frame; //< timecode frame data, ie. H M S frame rate

	void writeTrack() const;
    void readTrack() const;
	void drawMainMenu() const;
};
