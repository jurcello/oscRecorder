//
// Created by Jur de Vries on 14/04/2020.
//

#ifndef OSCRECORDER_TRACKRECORDER_H
#define OSCRECORDER_TRACKRECORDER_H

#include "Track.h"

template <typename MessageType>
class TrackRecorder {
public:
    TrackRecorder(Track<MessageType> *track)
    :track(track)
    {}

    void recordMessage(unsigned long time, MessageType message) {
        auto event = TrackEvent<MessageType>(time, message);
        track->addEvent(event);
    }

    void clear() {
        track->clear();
    }

private:
    Track<MessageType> *track;
};


#endif //OSCRECORDER_TRACKRECORDER_H
