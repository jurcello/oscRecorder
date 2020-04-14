//
// Created by Jur de Vries on 09/04/2020.
//

#ifndef OSCRECORDER_TRACK_H
#define OSCRECORDER_TRACK_H

#include <cstdint>
#include <vector>

template <typename MessageType>
struct TrackEvent {
    TrackEvent(uint64_t time)
    :millis(time)
    {}

    uint64_t millis;
    MessageType message;
};

template <typename MessageType>
class Track {
private:
    using TrackEventList = std::vector<TrackEvent<MessageType>>;

public:
    using iterator = typename TrackEventList::iterator;
    using const_iterator = typename TrackEventList::const_iterator;

    Track() {}

    void addEvent(TrackEvent<MessageType> event) {
        auto insertAt = getInsertIterator(event);
        events.insert(insertAt, event);
    }

    unsigned long size() {
        return events.size();
    }

    Track<MessageType>::iterator begin() {
        return events.begin();
    }

    Track<MessageType>::iterator end() {
        return events.end();
    }

    Track<MessageType>::iterator getIteratorFrom(uint64_t millisToFind) {
        return events.begin() + findIndexAtTime(millisToFind);
    }

    TrackEvent<MessageType> getEventAt(unsigned long pos) {
        return events.at(pos);
    }

    unsigned long findIndexAtTime(u_int64_t millisToFind) {
        unsigned long index = 0;
        while (index < events.size() && events[index].millis < millisToFind)
            index++;
        return index;
    }

private:
    TrackEventList events;

    const_iterator getInsertIterator(const TrackEvent<MessageType> &event) const {
        auto insertAt = getInsertIteratorFromStartOrEnd(event);
        while (insertAt != events.end() && (*insertAt).millis < event.millis) {
            insertAt++;
        }
        return insertAt;
    }

    const_iterator getInsertIteratorFromStartOrEnd(const TrackEvent<MessageType> &event) const {
        auto insertAt = events.begin();
        if (events.size() > 0 && events[events.size()].millis < event.millis) {
            insertAt = events.end() - 1;
        }
        return insertAt;
    }
};


#endif //OSCRECORDER_TRACK_H
