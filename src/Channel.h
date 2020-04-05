//
//  Channel.hpp
//  oscRecorder
//
//  Created by Jur de Vries on 05/04/2020.
//

#ifndef Channel_h
#define Channel_h

#include <stdio.h>
#include "ofxOsc.h"

struct OscEvent {
    OscEvent(ofxOscMessage message, uint64_t time);
    
    uint64_t millis;
    ofxOscMessage message;
};

class Channel {
public:
    Channel();
    void recordMessage(ofxOscMessage m, uint64_t time);
    bool hasMessages(uint64_t time);
    ofxOscMessage getMessage(uint64_t time);
    void rewind();
    void clear();
    
private:
    std::vector<OscEvent> oscMessages;
    int currentMessagePos;
};

#endif /* Channel_h */
