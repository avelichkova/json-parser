#include "catch2/catch_all.hpp"
#include "Commands.h"

TEST_CASE("open") {
    Commands commands;

    SECTION("Valid file name") {
        REQUIRE_NOTHROW(commands.open("valid.json"));
    }

    SECTION("Invalid file name") {
        REQUIRE_THROWS_AS(commands.open("invalid.txt"), std::runtime_error);
    }

    SECTION("File already open") {
        commands.open("valid.json");
        REQUIRE_THROWS_AS(commands.open("another.json"), std::invalid_argument);
    }
}

TEST_CASE("toLower") {
    Commands commands;

    SECTION("Convert to lowercase") {
        std::string str = "HELLO";
        commands.toLower(str);
        REQUIRE(str == "hello");
    }

    SECTION("Already lowercase") {
        std::string str = "world";
        commands.toLower(str);
        REQUIRE(str == "world");
    }
}