//
// Created by Jur de Vries on 09/04/2020.
//

#ifndef OSCRECORDER_GENERALTRACK_H
#define OSCRECORDER_GENERALTRACK_H

#include <cstdint>
#include <vector>

struct TrackEvent {
    TrackEvent(uint64_t time);
    uint64_t millis;
};

class GeneralTrack {
private:
    typedef std::vector<TrackEvent> TrackEventList;

public:
    typedef TrackEventList::iterator iterator;
    typedef TrackEventList::const_iterator const_iterator;

    GeneralTrack();
    void addEvent(TrackEvent event);
    unsigned long size();
    GeneralTrack::iterator begin();
    GeneralTrack::iterator end();
    GeneralTrack::iterator getIteratorFrom(uint64_t millisToFind);

    TrackEvent getEventAt(unsigned long pos);
    unsigned long findIndexAtTime(u_int64_t millisToFind);

private:
    int numberOfEvents;
    std::vector<TrackEvent> events;

    std::vector<TrackEvent, std::allocator<TrackEvent>>::const_iterator getInsertIterator(const TrackEvent &event) const;
    std::vector<TrackEvent, std::allocator<TrackEvent>>::const_iterator getInsertIteratorFromStartOrEnd(const TrackEvent &event) const;
};


#endif //OSCRECORDER_GENERALTRACK_H
