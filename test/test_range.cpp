#include "catch.hpp"

#include <xtl/range.h>


TEST_CASE("Range iterates over the currect values", "[xtl][range]") {
    constexpr int Begin = 0;
    constexpr int End = 100;

    SECTION("char range") {
        char start = 0;
        for (const auto i : xtl::range<char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("signed char range") {
        signed char start = 0;
        for (const auto i : xtl::range<signed char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned char range") {
        unsigned char start = 0;
        for (const auto i : xtl::range<unsigned char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("short range") {
        short start = 0;
        for (const auto i : xtl::range<short, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned short range") {
        unsigned short start = 0;
        for (const auto i : xtl::range<unsigned short, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("int range") {
        int start = 0;
        for (const auto i : xtl::int_range<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned range") {
        unsigned start = 0;
        for (const auto i : xtl::unsigned_range<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("long range") {
        long start = 0;
        for (const auto i : xtl::range<long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("long long range") {
        long long start = 0;
        for (const auto i : xtl::range<long long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned long long range") {
        unsigned long long start = 0;
        for (const auto i : xtl::range<unsigned long long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("size_t range") {
        size_t start = 0;
        for (const auto i : xtl::size_range<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }
}
