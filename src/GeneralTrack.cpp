//
// Created by Jur de Vries on 09/04/2020.
//

#include "GeneralTrack.h"

TrackEvent::TrackEvent(uint64_t time)
        :millis(time)
{
}

GeneralTrack::GeneralTrack()
        :numberOfEvents(0)
{
}

void GeneralTrack::addEvent(TrackEvent event) {
    auto insertAt = getInsertIterator(event);
    events.insert(insertAt, event);
}

std::vector<TrackEvent, std::allocator<TrackEvent>>::const_iterator GeneralTrack::getInsertIterator(const TrackEvent &event) const {
    auto insertAt = getInsertIteratorFromStartOrEnd(event);
    while (insertAt != events.end() && (*insertAt).millis < event.millis) {
        insertAt++;
    }
    return insertAt;
}

std::vector<TrackEvent, std::allocator<TrackEvent>>::const_iterator GeneralTrack::getInsertIteratorFromStartOrEnd(const TrackEvent &event) const {
    auto insertAt = events.begin();
    if (events.size() > 0 && events[events.size()].millis < event.millis) {
        insertAt = events.end() - 1;
    }
    return insertAt;
}

unsigned long GeneralTrack::size() {
    return events.size();
}

GeneralTrack::iterator GeneralTrack::begin() {
    return events.begin();
}

GeneralTrack::iterator GeneralTrack::end() {
    return events.end();
}

TrackEvent GeneralTrack::getEventAt(unsigned long pos) {
    return events.at(pos);
}

unsigned long GeneralTrack::findIndexAtTime(u_int64_t millisToFind) {
    unsigned long index = 0;
    while (index < events.size() && events[index].millis < millisToFind)
        index++;
    return index;
}

GeneralTrack::iterator GeneralTrack::getIteratorFrom(uint64_t millisToFind) {
    return events.begin() + findIndexAtTime(millisToFind);
}



