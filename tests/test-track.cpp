#include "catch.hh"
#include "GeneralTrack.h"

TrackEvent<float> createTrackEvent(uint64_t millis) {
    TrackEvent<float> event(0);
    return event;
}

TEST_CASE("A TrackEvent can be added to the track", "[GeneralTrack]") {
    GeneralTrack<float> track;
    TrackEvent<float> event = createTrackEvent(0);
    track.addEvent(event);
}

TEST_CASE("A new GeneralTrack has a size of 0 when created", "[GeneralTrack") {
    GeneralTrack<float> track;
    REQUIRE( track.size() == 0);
}

TEST_CASE("When an event is added to track, the size increases", "[GeneralTrack]") {
    GeneralTrack<float> track;
    TrackEvent<float> event = createTrackEvent(0);
    track.addEvent(event);
    REQUIRE(track.size() == 1);
    TrackEvent<float> event2 = createTrackEvent(1);
    track.addEvent(event2);
    REQUIRE(track.size() == 2);
}

TEST_CASE("When an event is added to the track, it can be retrieved", "[GeneralTrack]") {
    GeneralTrack<float> track;
    TrackEvent<float> event1 = createTrackEvent(10);
    track.addEvent(event1);
    TrackEvent<float> event2 = createTrackEvent(20);
    track.addEvent(event2);
    REQUIRE(track.getEventAt(0).millis == event1.millis);
    REQUIRE(track.getEventAt(1).millis == event2.millis);
}

TEST_CASE("When more than 1 events are added, they are inserted based on time ", "[GeneralTrack]") {
    GeneralTrack<float> track;
    TrackEvent<float> event1 = createTrackEvent(0);
    track.addEvent(event1);
    TrackEvent<float> event2 = createTrackEvent(40);
    track.addEvent(event2);
    TrackEvent<float> event3 = createTrackEvent(20);
    track.addEvent(event3);
    CHECK(track.getEventAt(0).millis == event1.millis);
    CHECK(track.getEventAt(1).millis == event3.millis);
    CHECK(track.getEventAt(2).millis == event2.millis);
}

TEST_CASE("The general track has begin and end iterators", "[GeneralTrack]") {
    GeneralTrack<float> track;
    TrackEvent<float> event1 = createTrackEvent(0);
    track.addEvent(event1);
    TrackEvent<float> event2 = createTrackEvent(20);
    track.addEvent(event2);
    TrackEvent<float> event3 = createTrackEvent(40);
    track.addEvent(event3);
    CHECK((*track.begin()).millis == event1.millis);
    CHECK((*(track.begin()+1)).millis == event2.millis);
    CHECK((*(track.end()-1)).millis == event3.millis);
}

TEST_CASE("The general track has a method to find the first event index with a certain time", "[GeneralTrack]") {
    GeneralTrack<float> track;
    track.addEvent(TrackEvent<float>(0));
    track.addEvent(TrackEvent<float>(10));
    track.addEvent(TrackEvent<float>(20));
    track.addEvent(TrackEvent<float>(30));
    CHECK(track.findIndexAtTime(10) == 1);
    CHECK(track.findIndexAtTime(25) == 3);
}

TEST_CASE("The general track has a method to find the first iterator with a certain time minimum", "[GeneralTrack]") {
    GeneralTrack<float> track;
    track.addEvent(TrackEvent<float>(0));
    track.addEvent(TrackEvent<float>(10));
    track.addEvent(TrackEvent<float>(20));
    track.addEvent(TrackEvent<float>(30));
    CHECK((*track.getIteratorFrom(10)).millis == 10);
    CHECK((*track.getIteratorFrom(15)).millis == 20);
}