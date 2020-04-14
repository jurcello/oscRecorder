#include "catch.hh"
#include "Track.h"

typedef Track<float> FloatTrack;
typedef TrackEvent<float> FloatEvent;

FloatEvent createTrackEvent(uint64_t millis, float message) {
    FloatEvent event(millis);
    event.message = message;
    return event;
}

TEST_CASE("A TrackEvent can be added to the track", "[GeneralTrack]") {
    FloatTrack track;
    FloatEvent event = createTrackEvent(0, 0.f);
    track.addEvent(event);
}

TEST_CASE("A new GeneralTrack has a size of 0 when created", "[GeneralTrack") {
    FloatTrack track;
    REQUIRE( track.size() == 0);
}

TEST_CASE("When an event is added to track, the size increases", "[GeneralTrack]") {
    FloatTrack track;
    FloatEvent event = createTrackEvent(0, 0.f);
    track.addEvent(event);
    REQUIRE(track.size() == 1);
    FloatEvent event2 = createTrackEvent(1, 0.f);
    track.addEvent(event2);
    REQUIRE(track.size() == 2);
}

TEST_CASE("When an event is added to the track, it can be retrieved", "[GeneralTrack]") {
    FloatTrack track;
    FloatEvent event1 = createTrackEvent(10, 1.f);
    track.addEvent(event1);
    FloatEvent event2 = createTrackEvent(20, 2.f);
    track.addEvent(event2);
    REQUIRE(track.getEventAt(0).message == 1.f);
    REQUIRE(track.getEventAt(1).message == 2.f);
}

TEST_CASE("When more than 1 events are added, they are inserted based on time ", "[GeneralTrack]") {
    FloatTrack track;
    FloatEvent event1 = createTrackEvent(0, 0.f);
    track.addEvent(event1);
    FloatEvent event2 = createTrackEvent(40, 1.f);
    track.addEvent(event2);
    FloatEvent event3 = createTrackEvent(20, 0.5f);
    track.addEvent(event3);
    CHECK(track.getEventAt(0).millis == 0);
    CHECK(track.getEventAt(1).millis == 20);
    CHECK(track.getEventAt(2).millis == 40);
}

TEST_CASE("The general track has begin and end iterators", "[GeneralTrack]") {
    FloatTrack track;
    FloatEvent event1 = createTrackEvent(0, 0.f);
    track.addEvent(event1);
    FloatEvent event2 = createTrackEvent(20, .5f);
    track.addEvent(event2);
    FloatEvent event3 = createTrackEvent(40, 1.f);
    track.addEvent(event3);
    CHECK((*track.begin()).millis == 0);
    CHECK((*(track.begin()+1)).millis == 20);
    CHECK((*(track.end()-1)).millis == 40);
}

TEST_CASE("The general track has a method to find the first event index with a certain time", "[GeneralTrack]") {
    FloatTrack track;
    track.addEvent(TrackEvent<float>(0));
    track.addEvent(TrackEvent<float>(10));
    track.addEvent(TrackEvent<float>(20));
    track.addEvent(TrackEvent<float>(30));
    CHECK(track.findIndexAtTime(10) == 1);
    CHECK(track.findIndexAtTime(25) == 3);
}

TEST_CASE("The general track has a method to find the first iterator with a certain time minimum", "[GeneralTrack]") {
    FloatTrack track;
    track.addEvent(TrackEvent<float>(0));
    track.addEvent(TrackEvent<float>(10));
    track.addEvent(TrackEvent<float>(20));
    track.addEvent(TrackEvent<float>(30));
    CHECK((*track.getIteratorFrom(10)).millis == 10);
    CHECK((*track.getIteratorFrom(15)).millis == 20);
}