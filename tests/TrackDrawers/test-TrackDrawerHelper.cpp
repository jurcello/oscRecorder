#include "catch.hh"
#include "TrackDrawerHelper.h"
#include "RulerData.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "IncompatibleTypes"

uint64_t secondsToMillis(uint64_t seconds) {
    return seconds*1000;
}

TEST_CASE("The max time can be set in milliseconds", "[TrackDrawerHelper]") {
    TrackDrawerHelper trackDrawer;
    uint64_t millis = 10 * 1000;
    trackDrawer.setMaxTimeMillis(millis);
    REQUIRE(trackDrawer.getMaxTimeMillis() == 10000);
}

TEST_CASE("Pixels per second can be set resulting in different content sizes", "[TrackDrawerHelper]") {
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(1.f);
    trackDrawer.setMaxTimeMillis(1000);

    REQUIRE(trackDrawer.getContentSize() == 1);

    SECTION("Pixels per second of 1 and max 10 of seconds") {
        trackDrawer.setMaxTimeMillis(10000);
        REQUIRE(trackDrawer.getContentSize() == 10);
    }

    SECTION("Pixels per second of 4 and max 50 of seconds") {
        trackDrawer.setPixelsPerSecond(4.f);
        trackDrawer.setMaxTimeMillis(50*1000);
        REQUIRE(trackDrawer.getContentSize() == 200);
    }

    SECTION("Pixels per second of 0.5 and max 50 of seconds") {
        trackDrawer.setPixelsPerSecond(.5f);
        trackDrawer.setMaxTimeMillis(50*1000);
        REQUIRE(trackDrawer.getContentSize() == 25);
    }
}

TEST_CASE("Ruler data for every 5 seconds can be retrieved", "[TrackDrawerHelper]")
{
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(20.f);
    SECTION("No ruler data due to low max time") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(1));
        std::vector<RulerData> rulerData = trackDrawer.getRuler5SecondData();
        REQUIRE(rulerData.size() == 0);
    }
    SECTION("One ruler point for the 5 second case") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(5));
        std::vector<RulerData> rulerData = trackDrawer.getRuler5SecondData();
        REQUIRE(rulerData[0].x == 100);
        REQUIRE(rulerData[0].text == "00:05");
    }
    SECTION("Two ruler points for the 5 and 10 second case") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(11));
        std::vector<RulerData> rulerData = trackDrawer.getRuler5SecondData();
        REQUIRE(rulerData[0].x == 100);
        REQUIRE(rulerData[0].text == "00:05");
        REQUIRE(rulerData[1].x == 200);
        REQUIRE(rulerData[1].text == "00:10");
    }
    SECTION("For a point that exceeds a minute, the minute should be located before the semicolon") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(130));
        std::vector<RulerData> rulerData = trackDrawer.getRuler5SecondData();
        REQUIRE(rulerData[12].x == 1300);
        REQUIRE(rulerData[12].text == "01:05");
        REQUIRE(rulerData[13].text == "01:10");
        REQUIRE(rulerData[24].text == "02:05");

    }
}

#pragma clang diagnostic pop