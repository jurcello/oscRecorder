#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mTimeline = Timeline();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Hi, this will be the osc recorder", 20., 20.);
    ofDrawBitmapString("Press 's' to start, 't' to stop, 'space' to toggle and 'r' to rewind", 20., 40.);
    ofDrawBitmapString("Elapsed seoonds: " + ofToString(mTimeline.elapsedSeconds()), 20, 80);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            mTimeline.start();
            break;
        
        case 't':
            mTimeline.stop();
            break;
            
        case 'r':
            mTimeline.reset();
            break;
            
        case ' ':
            mTimeline.startStop();
            break;
            
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
