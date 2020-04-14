//
// Created by Jur de Vries on 14/04/2020.
//

#ifndef OSCRECORDER_TRACKRECORDER_H
#define OSCRECORDER_TRACKRECORDER_H

#include "Track.h"

template <typename MessageType>
class TrackRecorder {
public:
    TrackRecorder(Track<MessageType> *track);

    void recordMessage(unsigned long time, MessageType message);

    void clear();

private:
    Track<MessageType> *track;
};

template <typename MessageType>
TrackRecorder<MessageType>::TrackRecorder(Track<MessageType> *track)
:track(track)
{
}

template <typename MessageType>
void TrackRecorder<MessageType>::recordMessage(unsigned long time, MessageType message) {
    auto event = TrackEvent<MessageType>(time, message);
    track->addEvent(event);
}

template <typename MessageType>
void TrackRecorder<MessageType>::clear() {
    track->clear();
}

#endif //OSCRECORDER_TRACKRECORDER_H
