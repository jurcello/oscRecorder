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

    timecodeSyncer = MidiTimecodeSync::create(timeline);
    timecodeSyncer->setup();
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
            timelineUI->setOutputMessage(lastMessage);
            sender.sendMessage(lastMessage);
        }
    }
    timecodeSyncer->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawUI();
}

void ofApp::drawUI() {
    gui.begin();
    {
        drawMainMenu();
        timelineUI->drawUi(20);
        tracksUI.setHeight(140);
        tracksUI.draw(timeline, trackChannel, 80);
        tracksUI.playing = timeline.running();
    }
    gui.end();
}

void ofApp::drawMainMenu() const {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open"))
            {
                readTrack();
            }
            if (ImGui::MenuItem("Save"))
            {
                writeTrack();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
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
            // TODO: Make listener on timeline.
            timeline.reset();
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

void ofApp::exit() {
    timecodeSyncer->exit();
}

