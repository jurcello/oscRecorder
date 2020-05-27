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

    midiIn.openVirtualPort("OSC Recorder input");
    midiIn.ignoreTypes(false, // sysex  <-- don't ignore timecode messages!
            false, // timing <-- don't ignore clock messages!
            true); // sensing

    // add ofApp as a listener
    midiIn.addListener(this);
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

    // MIDI TIMECODE

    // if we havent received a quareter frame message from the timecode master,
    // assume playback has stopped
    if(timecodeRunning && ofGetElapsedTimeMillis() - timecodeTimestamp > 100) {
        ofLog() << "timecode stopped";
        timecodeRunning = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    drawUI();
    // MIDI CLOCK

    ofDrawBitmapString((clockRunning ? "MIDI clock: running" : "MIDI clock: stopped"), 20, 30);
    ofDrawBitmapString("pos MIDI beats: "+ofToString(beats), 20, 58);
    ofDrawBitmapString("pos seconds: "+ofToString(seconds), 20, 74);
    ofDrawBitmapString("bpm: "+ofToString(round(bpm)), 20, 90);

    // a MIDI beat is a 16th note, so do a little math to convert to a time signature:
    // 4/4 -> 4 notes per bar & quarter note = 1 beat, add 1 to count from 1 instead of 0
    int quarters = beats / 4; // convert total # beats to # quarters
    int bars = (quarters / 4) + 1; // compute # of bars
    int beatsInBar = (quarters % 4) + 1; // compute remainder as # notes within the current bar
    ofDrawBitmapString("4/4 bars: "+ofToString(bars)+" beat: "+ofToString(beatsInBar), 20, 106);

    ofDrawBitmapString((timecodeRunning ? "MIDI timecode: running" : "MIDI timecode: stopped"), 20, 160);
    ofDrawBitmapString("pos time: "+frame.toString(), 20, 188);
    ofDrawBitmapString("pos seconds: "+ofToString(frame.toSeconds()), 20, 204);
    ofDrawBitmapString("framerate: "+ofToString(ofxMidiTimecode::rateToFps(frame.rate)), 20, 220);
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

void ofApp::newMidiMessage(ofxMidiMessage &message) {
    // MIDI CLOCK

    // update the clock length and song pos in beats
    if(clock.update(message.bytes)) {
        // we got a new song pos
        beats = clock.getBeats();
        seconds = clock.getSeconds();
    }

    // compute the seconds and bpm
    switch(message.status) {

        // compute seconds and bpm live, you may or may not always need this
        // which is why it is not integrated into the ofxMidiClock parser class
        case MIDI_TIME_CLOCK:
            seconds = clock.getSeconds();
            bpm += (clock.getBpm() - bpm) / 5; // average the last 5 bpm values
            // no break here so the next case statement is checked,
            // this way we can set clockRunning if we've missed a MIDI_START
            // ie. master was running before we started this example

            // transport control
        case MIDI_START: case MIDI_CONTINUE:
            if(!clockRunning) {
                clockRunning = true;
                ofLog() << "clock started";
            }
            break;
        case MIDI_STOP:
            if(clockRunning) {
                clockRunning = false;
                ofLog() << "clock stopped";
            }
            break;

        default:
            break;
    }

    if(timecode.update(message.bytes)) {

        // we got a new frame pos
        frame = timecode.getFrame();

        // if the last message was a timecode quarter frame message,
        // then assume the timecode master has started playback
        if(message.status == MIDI_TIME_CODE) {
            if(!timecodeRunning) {
                timecodeRunning = true;
                ofLog() << "timecode started";
            }
            timecodeTimestamp = ofGetElapsedTimeMillis();
        }
    }
}

void ofApp::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

