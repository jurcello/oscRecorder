#pragma once

#include "ofMain.h"
#include "timeline.h"
#include "ofxOsc.h"
#include "TrackChannel.h"
#include "ofxImGui.h"
#include "TimelineUI.h"
#include "TracksWindowUI.h"
#include "MidiTimecodeSync.h"

#define IN_PORT 9900
#define OUT_PORT 1100

class ofApp : public ofBaseApp {

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

    MidiTimecodeSyncRef timecodeSyncer;

	void writeTrack() const;
    void readTrack() const;
	void drawMainMenu() const;
};
