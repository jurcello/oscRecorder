#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    timeline = Timeline();
    recording = false;
    receiver.setup(IN_PORT);
    sender.setup("localhost", OUT_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!timeline.running()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        sender.sendMessage(m);
    }
    if (timeline.running() && receiver.hasWaitingMessages() && recording) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        oscChannel.recordMessage(m, timeline.elapsedMillis());
        sender.sendMessage(m);
    }
    if (timeline.running() && !recording) {
        while (oscChannel.hasMessages(timeline.elapsedMillis())) {
            lastMessage = oscChannel.getMessage(timeline.elapsedMillis());
            sender.sendMessage(lastMessage);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Hi, this will be the osc recorder", 20., 20.);
    ofDrawBitmapString("Press 's' to start, 't' to stop, 'space' to toggle and 'r' to rewind", 20., 40.);
    ofDrawBitmapString("Elapsed time: " + timeline.timecode(), 20, 120);
    std::string rec = recording ? "recording" : "playing";
    ofDrawBitmapString(rec, 20, 140);
    if (lastMessage.getNumArgs() > 0) {
        ofDrawBitmapString("Last osc message: " + lastMessage.getAddress() + ofToString(lastMessage.getArgAsFloat(0)), 20, 160);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            timeline.start();
            oscChannel.rewind();
            if (recording) {
                oscChannel.clear();
            }
            break;
        
        case 't':
            timeline.stop();
            recording = false;
            break;
            
        case 'r':
            timeline.reset();
            oscChannel.rewind();
            break;
            
        case ' ':
            timeline.startStop();
            break;
        
        case 'm':
            recording = !recording;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
