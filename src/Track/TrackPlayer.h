//
// Created by Jur de Vries on 14/04/2020.
//

#ifndef OSCRECORDER_TRACKPLAYER_H
#define OSCRECORDER_TRACKPLAYER_H

#include "Track.h"
#include <exception>

class noNewMessageException: public std::exception
{} noNew;

template <typename MessageType>
class TrackPlayer {
public:
    TrackPlayer(Track<MessageType> *track)
    :track(track), currentPosition(0)
    {}

    MessageType getNextMessage(uint64_t time) {
        if (! this->hasMessages(time)) {
            throw noNew;
        }
        return track->getEventAt(currentPosition++).message;
    }

    bool hasMessages(uint64_t time) {
        return currentPosition < track->size() && track->getEventAt(currentPosition).millis <= time;
    }

    void seek(u_int64_t time) {
        currentPosition = track->findIndexAtTime(time);
    }

    void rewind() {
        currentPosition = 0;
    }

    uint64_t timeLength() {
        return track->getEventAt(track->size() - 1).millis;
    }

private:
    Track<MessageType> *track;
    unsigned long currentPosition;
};


#endif //OSCRECORDER_TRACKPLAYER_H
