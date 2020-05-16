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

TEST_CASE("Ruler data for every second can be retrieved", "[TrackDrawerHelper]")
{
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(20.f);
    SECTION("Only one ruler data due to low max time") {
        trackDrawer.setMaxTimeMillis(500);
        std::vector<RulerData> rulerData = trackDrawer.getRulerData();
        REQUIRE(rulerData.size() == 1);
    }
    SECTION("Every second there is ruler data without text when second is not multiple of 5") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(8));
        std::vector<RulerData> rulerData = trackDrawer.getRulerData();
        REQUIRE(rulerData[0].hasText);
        REQUIRE(!rulerData[1].hasText);
        REQUIRE(!rulerData[2].hasText);
        REQUIRE(!rulerData[3].hasText);
        REQUIRE(!rulerData[4].hasText);
        REQUIRE(rulerData[5].hasText);
        REQUIRE(!rulerData[6].hasText);
        REQUIRE(!rulerData[7].hasText);
    }
    SECTION("One ruler point with text for the 5 second case") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(5));
        std::vector<RulerData> rulerData = trackDrawer.getRulerData();
        REQUIRE(rulerData[5].x == 100);
        REQUIRE(rulerData[5].hasText);
        REQUIRE(rulerData[5].text == "00:05");
    }
    SECTION("Two ruler points with text for the 5 and 10 second case") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(11));
        std::vector<RulerData> rulerData = trackDrawer.getRulerData();
        REQUIRE(rulerData[5].x == 100);
        REQUIRE(rulerData[5].hasText);
        REQUIRE(rulerData[5].text == "00:05");
        REQUIRE(rulerData[10].x == 200);
        REQUIRE(rulerData[10].hasText);
        REQUIRE(rulerData[10].text == "00:10");
    }
    SECTION("For a point that exceeds a minute, the minute should be located before the semicolon") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(130));
        std::vector<RulerData> rulerData = trackDrawer.getRulerData();
        REQUIRE(rulerData[65].x == 1300);
        REQUIRE(rulerData[65].hasText);
        REQUIRE(rulerData[65].text == "01:05");
        REQUIRE(rulerData[70].hasText);
        REQUIRE(rulerData[70].text == "01:10");
        REQUIRE(rulerData[125].hasText);
        REQUIRE(rulerData[125].text == "02:05");

    }
}

TEST_CASE("The position of time marker can be retrieved", "[TrackDrawerHelper]") {
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(20.f);
    SECTION("When no current time is set, the position of the time marker is zero.") {
        REQUIRE(trackDrawer.getTimeMarkerPosition() == 0);
    }
    SECTION("When current time is set, the position of the time marker is is properly calculated.") {
        trackDrawer.setCurrentTimeMillis(secondsToMillis(1));
        REQUIRE(trackDrawer.getTimeMarkerPosition() == 20);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(2));
        REQUIRE(trackDrawer.getTimeMarkerPosition() == 40);
        trackDrawer.setPixelsPerSecond(30.f);
        REQUIRE(trackDrawer.getTimeMarkerPosition() == 60);
    }
}

TEST_CASE("The position of the content can be centered based on the time", "[TrackDrawerHelper]") {
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(20.f);

    SECTION("When the width of the content is the same as the window with, the scrollOffset is 0") {
        trackDrawer.setMaxTimeMillis(secondsToMillis(10));
        trackDrawer.setCurrentWindowWidth(200);
        REQUIRE(trackDrawer.getScrollOffset() == 0);
    }

   SECTION("When the width of the content is twice the window with, and the time is half max time") {
        trackDrawer.setPixelsPerSecond(1.f);
        trackDrawer.setMaxTimeMillis(secondsToMillis(200));
        trackDrawer.setCurrentWindowWidth(100);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(100));
        REQUIRE(trackDrawer.getScrollOffset() == 50);
    }

   SECTION("When the width of the content is twice the window with, and the time is a bit after a quarter of the time") {
        trackDrawer.setPixelsPerSecond(1.f);
        trackDrawer.setMaxTimeMillis(secondsToMillis(200));
        trackDrawer.setCurrentWindowWidth(100);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(60));
        REQUIRE(trackDrawer.getScrollOffset() == 10);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(80));
        REQUIRE(trackDrawer.getScrollOffset() == 30);
    }
   SECTION("When the time is earlier than the time on half the window from the start, there is no offset") {
        trackDrawer.setPixelsPerSecond(2.f);
        trackDrawer.setMaxTimeMillis(secondsToMillis(400));
        trackDrawer.setCurrentWindowWidth(100);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(20));
        REQUIRE(trackDrawer.getScrollOffset() == 0);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(25));
        REQUIRE(trackDrawer.getScrollOffset() == 0);
    }
    SECTION("When the time nears the end, the offset stays the same") {
        trackDrawer.setPixelsPerSecond(1.f);
        trackDrawer.setMaxTimeMillis(secondsToMillis(200));
        trackDrawer.setCurrentWindowWidth(100);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(150));
        REQUIRE(trackDrawer.getScrollOffset() == 100);
        trackDrawer.setCurrentTimeMillis(secondsToMillis(170));
        REQUIRE(trackDrawer.getScrollOffset() == 100);
    }

}

TEST_CASE("A pixel position can be transformed to a millisecond value" "[TrackDrawerHelper]") {
    TrackDrawerHelper trackDrawer;
    trackDrawer.setPixelsPerSecond(100.f);
    trackDrawer.setMaxTimeMillis(secondsToMillis(200));
    REQUIRE(trackDrawer.getMillisFromPixels(0) == 0);
    REQUIRE(trackDrawer.getMillisFromPixels(100) == 1000);
    REQUIRE(trackDrawer.getMillisFromPixels(200) == 2000);
    trackDrawer.setPixelsPerSecond(50.f);
    REQUIRE(trackDrawer.getMillisFromPixels(200) == 4000);
}

#pragma clang diagnostic pop