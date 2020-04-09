#include "catch.hh"
#include "OscTrack.h"
#include "ofxOsc.h"

TEST_CASE("There is a OscTrack class", "[OscTrack]") {
    OscTrack track;
}

TEST_CASE("There is an OscEvent struct", "[OscEvent]") {
    OscEvent event;
}

TEST_CASE("The OscEvent has members for time in millis and events", "[OscEvent]") {
    OscEvent event;
    event.millis = 0;
    event.event;
}