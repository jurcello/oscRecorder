#pragma once

#include "ofMain.h"
#include "timeline.h"
#include "ofxOsc.h"
#include "TrackChannel.h"

#define IN_PORT 9900
#define OUT_PORT 1100

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		
private:
    Timeline timeline;
    ofxOscReceiver receiver;
    ofxOscSender sender;
    bool recording;
    TrackChannel trackChannel;
    ofxOscMessage lastMessage;
};
