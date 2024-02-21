#include "catch2/catch_all.hpp"
#include "JSONTree.h"

TEST_CASE("JSONTree::distance") {
    JSONTree jsonTree;

    SECTION("Distance of 0") {
        REQUIRE(jsonTree.distance(0) == "");
    }

    SECTION("Distance of 1") {
        REQUIRE(jsonTree.distance(1) == " ");
    }

    SECTION("Distance of 5") {
        REQUIRE(jsonTree.distance(5) == "     ");
    }
}

