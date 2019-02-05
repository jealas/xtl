#include "catch.hpp"

#include <xtl/range.h>


TEST_CASE("Range iterates over the currect values", "[xtl][range]") {
    constexpr int Begin = 0;
    constexpr int End = 100;

    SECTION("char range") {
        char start = 0;
        for (const auto i : xtl::crange<char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("signed char range") {
        signed char start = 0;
        for (const auto i : xtl::crange<signed char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned char range") {
        unsigned char start = 0;
        for (const auto i : xtl::crange<unsigned char, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("short range") {
        short start = 0;
        for (const auto i : xtl::crange<short, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned short range") {
        unsigned short start = 0;
        for (const auto i : xtl::crange<unsigned short, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("int range") {
        int start = 0;
        for (const auto i : xtl::int_crange<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned range") {
        unsigned start = 0;
        for (const auto i : xtl::unsigned_crange<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("long range") {
        long start = 0;
        for (const auto i : xtl::crange<long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("long long range") {
        long long start = 0;
        for (const auto i : xtl::crange<long long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("unsigned long long range") {
        unsigned long long start = 0;
        for (const auto i : xtl::crange<unsigned long long, Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }

    SECTION("size_t range") {
        size_t start = 0;
        for (const auto i : xtl::size_crange<Begin, End>) {
            REQUIRE(start++ == i);
        }

        REQUIRE(start == End);
    }
}
