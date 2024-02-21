#include "catch2/catch_all.hpp"
#include "Tokenizer.h"

TEST_CASE("readNull") {
    JSONTokenizer tokenizer;

    SECTION("Read null") {
        std::ifstream file("organisation.json");
        REQUIRE(tokenizer.readNull(file) == "null");
    }
}

TEST_CASE("readTrue") {
    JSONTokenizer tokenizer;

    SECTION("Read true") {
        std::ifstream file("organisation.json");
        REQUIRE(tokenizer.readTrue(file) == "true");
    }
}

TEST_CASE("readFalse") {
    JSONTokenizer tokenizer;

    SECTION("Read false") {
        std::ifstream file("organisation.json");
        REQUIRE(tokenizer.readFalse(file) == "false");
    }
}

TEST_CASE("readString") {
    JSONTokenizer tokenizer;

    SECTION("Read string") {
        std::ifstream file("organisation.json");
        REQUIRE(tokenizer.readString(file) == "test_string");
    }
}

