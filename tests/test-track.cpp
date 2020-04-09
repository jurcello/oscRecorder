#include "catch.hh"
#include "GeneralTrack.h"

TEST_CASE("The TrackEvent has members for time in millis and events", "[TrackEvent]") {
    TrackEvent event(0);
}

TEST_CASE("A TrackEvent can be added to the track", "[GeneralTrack]") {
    GeneralTrack track;
    TrackEvent event(0);
    track.addEvent(event);
}

TEST_CASE("A new GeneralTrack has a size of 0 when created", "[GeneralTrack") {
    GeneralTrack track;
    REQUIRE( track.size() == 0);
}

TEST_CASE("When an event is added to track, the size increases", "[GeneralTrack]") {
    GeneralTrack track;
    TrackEvent event(0);
    track.addEvent(event);
    REQUIRE(track.size() == 1);
    TrackEvent event2(1);
    track.addEvent(event2);
    REQUIRE(track.size() == 2);
}

TEST_CASE("When an event is added to the track, it can be retrieved", "[GeneralTrack]") {
    GeneralTrack track;
    TrackEvent event1(10);
    track.addEvent(event1);
    TrackEvent event2(20);
    track.addEvent(event2);
    REQUIRE(track.getEventAt(0).millis == event1.millis);
    REQUIRE(track.getEventAt(1).millis == event2.millis);
}

TEST_CASE("When more than 1 events are added, they are inserted based on time ", "[GeneralTrack]") {
    GeneralTrack track;
    TrackEvent event1(0);
    track.addEvent(event1);
    TrackEvent event2(40);
    track.addEvent(event2);
    TrackEvent event3(20);
    track.addEvent(event3);
    CHECK(track.getEventAt(0).millis == event1.millis);
    CHECK(track.getEventAt(1).millis == event3.millis);
    CHECK(track.getEventAt(2).millis == event2.millis);
}

TEST_CASE("The general track has begin and end iterators", "[GeneralTrack]") {
    GeneralTrack track;
    TrackEvent event1(0);
    track.addEvent(event1);
    TrackEvent event2(20);
    track.addEvent(event2);
    TrackEvent event3(40);
    track.addEvent(event3);
    CHECK((*track.begin()).millis == event1.millis);
    CHECK((*(track.begin()+1)).millis == event2.millis);
    CHECK((*(track.end()-1)).millis == event3.millis);
}

TEST_CASE("The general track has a method to find the first event index with a certain time", "[GeneralTrack]") {
    GeneralTrack track;
    track.addEvent(TrackEvent(0));
    track.addEvent(TrackEvent(10));
    track.addEvent(TrackEvent(20));
    track.addEvent(TrackEvent(30));
    CHECK(track.findIndexAtTime(10) == 1);
    CHECK(track.findIndexAtTime(25) == 3);
}

TEST_CASE("The general track has a method to find the first iterator with a certain time minimum", "[GeneralTrack]") {
    GeneralTrack track;
    track.addEvent(TrackEvent(0));
    track.addEvent(TrackEvent(10));
    track.addEvent(TrackEvent(20));
    track.addEvent(TrackEvent(30));
    CHECK((*track.getIteratorFrom(10)).millis == 10);
    CHECK((*track.getIteratorFrom(15)).millis == 20);
}