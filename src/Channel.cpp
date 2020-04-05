//
//  Channel.cpp
//  oscRecorder
//
//  Created by Jur de Vries on 05/04/2020.
//

#include "Channel.h"

OscEvent::OscEvent(ofxOscMessage message, uint64_t time)
:message(message), millis(time)
{}

Channel::Channel()
:currentMessagePos(0)
{}

void Channel::recordMessage(ofxOscMessage m, uint64_t time) {
    OscEvent e(m, time);
    oscMessages.push_back(e);
}

bool Channel::hasMessages(uint64_t time) {
    int nextPos = currentMessagePos + 1;
    return nextPos < oscMessages.size() && oscMessages[nextPos].millis < time;
}

ofxOscMessage Channel::getMessage(uint64_t time) {
    if (hasMessages(time)) {
        currentMessagePos++;
        return oscMessages[currentMessagePos].message;
    }
}

void Channel::rewind() {
    currentMessagePos = 0;
}

void Channel::clear() {
    oscMessages.clear();
    currentMessagePos = 0;
}
