#include "ofApp.h"
#include "TrackWriterReader.h"
#include "ofSystemUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
    timeline = Timeline();
    recording = false;
    receiver.setup(IN_PORT);
    sender.setup("localhost", OUT_PORT);
    gui.setup();
    timelineUI = TimelineUI::create(timeline, recording);
    ofxOscMessage m;
    lastMessage = m;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!timeline.running()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        sender.sendMessage(m);
        timelineUI->setInputMessage(m);
    }
    if (timeline.running() && receiver.hasWaitingMessages() && recording) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        trackChannel.recorder->recordMessage(timeline.elapsedMillis(), m);
        timelineUI->setInputMessage(m);
        sender.sendMessage(m);
    }
    if (timeline.running() && !recording) {
        while (trackChannel.player->hasMessages(timeline.elapsedMillis())) {
            lastMessage = trackChannel.player->getNextMessage(timeline.elapsedMillis());
            sender.sendMessage(lastMessage);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    std::string rec = recording ? "recording" : "playing";
    ofDrawBitmapString(rec, 20, 140);
    if (lastMessage.getNumArgs() > 0) {
        ofDrawBitmapString("Last osc message: " + lastMessage.getAddress() + ofToString(lastMessage.getArgAsFloat(0)), 20, 160);
    }

    drawUI();
}

void ofApp::drawUI() {
    gui.begin();
    {
        timelineUI->drawUi();
        tracksUI.draw(timeline, trackChannel);
        tracksUI.playing = timeline.running();
    }
    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            timeline.start();
            trackChannel.player->rewind();
            if (recording) {
                trackChannel.recorder->clear();
            }
            break;
        
        case 't':
            timeline.stop();
            recording = false;
            break;
            
        case 'r':
            timeline.reset();
            trackChannel.player->rewind();
            break;
            
        case ' ':
            timeline.startStop();
            break;
        
        case 'm':
            recording = !recording;
            break;

        case 'w':
            writeTrack();
            break;

        case 'l':
            readTrack();

        default:
            break;
    }
}

void ofApp::writeTrack() const {
    ofFileDialogResult result = ofSystemSaveDialog("track.json", "Save");
    if (result.bSuccess) {
        TrackWriterReader writer(trackChannel.track);
        writer.write(result.getPath());
    }
}

void ofApp::readTrack() const {
    ofFileDialogResult result = ofSystemLoadDialog("Load track");
    if (result.bSuccess) {
        TrackWriterReader reader(trackChannel.track);
        reader.readFromFile(result.getPath());
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

