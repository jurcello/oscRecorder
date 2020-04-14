#include "catch.hh"
#include "Track.h"
#include "TrackRecorder.h"

typedef Track<float> FloatTrack;
typedef TrackEvent<float> FloatEvent;
typedef TrackRecorder<float> FloatRecorder;

TEST_CASE("A track recorder can be made using a track.", "[TrackRecorder]") {
    FloatTrack track;
    FloatRecorder recorder(track);
}

TEST_CASE("The recorder can record a message at a specific millis time.", "[TrackRecoder]") {
    FloatTrack track;
    FloatRecorder recorder(track);
    recorder.recordMessage(0, 0.5f);
    REQUIRE(track.size() == 1);
    auto event = track.getEventAt(0);
    REQUIRE(event.millis == 0);
    REQUIRE(event.message == 0.5f);
}