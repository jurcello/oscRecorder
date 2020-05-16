#include "catch.hh"
#include "timeline.h"

TEST_CASE("The timeline can be set to a certain time before playing when stopped", "[timeline]") {
    Timeline timeline;
    timeline.setCurrentMillis(10);
    REQUIRE(timeline.millis() == 10);
}

TEST_CASE("The timeline can be set to a certain time multiple times", "[timeline]") {
    Timeline timeline;
    timeline.setCurrentMillis(10);
    REQUIRE(timeline.millis() == 10);
    timeline.setCurrentMillis(100);
    REQUIRE(timeline.millis() == 100);
}