#include "catch.hh"
#include "Track.h"
#include "TrackPlayer.h"

typedef Track<float> FloatTrack;
typedef TrackEvent<float> FloatEvent;
typedef TrackPlayer<float> FloatPlayer;

TEST_CASE("A track player has a method getNextMessage which returns the messages of the track one at a time", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    for (uint64_t i = 0; i < 5; i++) {
        track.addEvent(FloatEvent(i, .1f*i));
    }
    REQUIRE(player.getNextMessage(10) == 0.f);
    REQUIRE(player.getNextMessage(10) == .1f);
    REQUIRE(player.getNextMessage(10) == .2f);
    REQUIRE(player.getNextMessage(10) == .3f);
    REQUIRE(player.getNextMessage(10) == .4f);
}

TEST_CASE("The track player throws a runtime exception when there are no next messages at the end", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .1f));
    track.addEvent(FloatEvent(15, .1f));
    player.getNextMessage(20);
    player.getNextMessage(20);
    REQUIRE_THROWS_AS(player.getNextMessage(20), noNewMessageException);
}

TEST_CASE("The track player throws a runtime exception when there are no next messages at a certain time", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .1f));
    track.addEvent(FloatEvent(15, .1f));
    player.getNextMessage(10);
    REQUIRE_THROWS_AS(player.getNextMessage(10), noNewMessageException);
}

TEST_CASE("The track player has a method which indicates if there are still messages at a time", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .1f));
    track.addEvent(FloatEvent(15, .1f));
    REQUIRE(player.hasMessages(10));
    player.getNextMessage(10);
    REQUIRE(! player.hasMessages(10));
}

TEST_CASE("The track player has a seek method that sets the position to a certain time", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .0f));
    track.addEvent(FloatEvent(15, .1f));
    player.seek(15);
    REQUIRE(player.getNextMessage(15) == .1f);
}

TEST_CASE("The seek method supports seeking beyond the upper boundary of the track", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .0f));
    track.addEvent(FloatEvent(15, .1f));
    player.seek(1000);
    REQUIRE(! player.hasMessages(1000));
}

TEST_CASE("The track player has a rewind method that sets the player to 0", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .0f));
    track.addEvent(FloatEvent(15, .1f));
    REQUIRE(player.getNextMessage(15) == .0f);
    REQUIRE(player.getNextMessage(15) == .1f);
    player.rewind();
    REQUIRE(player.getNextMessage(15) == .0f);
}

TEST_CASE("The track player has a timeLength method that returns the length in milliseconds", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(200, .0f));
    uint64_t length = player.timeLength();
    REQUIRE(length == 200);
}

TEST_CASE("The track player seeks to the time if the hasMessages is called with a time lower than the last message", "[TrackPlayer]") {
    FloatTrack track;
    FloatPlayer player(&track);
    track.addEvent(FloatEvent(5, .0f));
    track.addEvent(FloatEvent(15, .1f));
    track.addEvent(FloatEvent(25, .2f));
    player.getNextMessage(25);
    player.getNextMessage(25);
    player.getNextMessage(25);
    player.hasMessages(15);
    REQUIRE(player.getNextMessage(15) == .1f);

}