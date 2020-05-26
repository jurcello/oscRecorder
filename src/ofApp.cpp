#include "ofApp.h"
#include "TrackWriter.h"
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

    // Delete later. Only for testing.
    for (int timeCode = 0; timeCode < 20000; timeCode += 500) {
        ofxOscMessage dummyMessage;
        dummyMessage.setAddress("/test");
        dummyMessage.addFloatArg(timeCode / 20000.f);
        trackChannel.recorder->recordMessage(timeCode, dummyMessage);
    }
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

        case 'l': {
            ofFileDialogResult result = ofSystemLoadDialog("Load track");
            if (result.bSuccess) {
                trackChannel.track->clear();
                ofxJSON info;
                info.open(result.getPath());
                for (auto &json: info["messages"]) {
                    ofxOscMessage m;
                    string address = json["address"].asString();
                    u_int64_t millis = static_cast<u_int64_t>(json["time"].asInt64());
                    m.setAddress(address);

                    for(auto & arg : json["args"]){
                        int typeInt = arg["type"].asInt();
                        ofxOscArgType type =ofxOscArgType(typeInt);

                        switch (type) {
                            case OFXOSC_TYPE_INT32: m.addIntArg(arg["value"].asInt()); break;
                            case OFXOSC_TYPE_INT64: m.addInt64Arg(arg["value"].asInt64()); break;
                            case OFXOSC_TYPE_FLOAT: m.addFloatArg(arg["value"].asFloat()); break;
                            case OFXOSC_TYPE_DOUBLE: m.addDoubleArg(arg["value"].asDouble()); break;
                            case OFXOSC_TYPE_STRING: m.addStringArg(arg["value"].asString()); break;
                            case OFXOSC_TYPE_SYMBOL: m.addSymbolArg(arg["value"].asString()); break;
                            case OFXOSC_TYPE_CHAR: m.addCharArg(char(arg["value"].asInt())); break;
                            case OFXOSC_TYPE_MIDI_MESSAGE: m.addIntArg(arg["value"].asInt()); break;
                            case OFXOSC_TYPE_TRUE: m.addBoolArg(arg["value"].asBool()); break;
                            case OFXOSC_TYPE_FALSE: m.addBoolArg(arg["value"].asBool()); break;
                            case OFXOSC_TYPE_TRIGGER: m.addBoolArg(arg["value"].asBool()); break;
                            case OFXOSC_TYPE_TIMETAG:  m.addInt64Arg(arg["value"].asInt64()); break;
                            case OFXOSC_TYPE_RGBA_COLOR: m.addIntArg(arg["value"].asInt()); break;
                            default: ofLogError("ofxOscRecorder") << "type not supported!";
                        }
                    }
                    trackChannel.recorder->recordMessage(millis, m);
                }
            }
        }

        default:
            break;
    }
}

void ofApp::writeTrack() const {
    ofFileDialogResult result = ofSystemSaveDialog("track.json", "Save");
    if (result.bSuccess) {
        TrackWriter writer(trackChannel.track);
        writer.write(result.getPath());
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

