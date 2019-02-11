#include "catch.hpp"

#include <initializer_list>

#include <xtl/utility.h>

template <class T, T ... Ints>
T test_integer_sequence(const xtl::integer_sequence<T, Ints...>) {
    T start = 0;
    for (const auto i : std::initializer_list<T>{Ints...}) {
        REQUIRE(start++ == i);
    }

    return start;
}


TEST_CASE("Can build integer sequences", "[xtl][utility]") {
    constexpr auto N = 100;

    SECTION("int") {
        SECTION("non-empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_integer_sequence<int, N>()) == N);
        }

        SECTION("empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_integer_sequence<int, 0>()) == 0);
        }
    }

    SECTION("size_t") {
        SECTION("non-empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_integer_sequence<size_t, N>()) == N);
        }

        SECTION("empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_integer_sequence<size_t, 0>()) == 0);
        }
    }
}

TEST_CASE("Can build index sequences", "[xtl][utility]") {
    constexpr auto N = 100;

    SECTION("int") {
        SECTION("non-empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_index_sequence<N>()) == N);
        }

        SECTION("empty sequence") {
            REQUIRE(test_integer_sequence(xtl::make_index_sequence<0>()) == 0);
        }
    }
}

TEST_CASE("Index sequence for list of types returns correct index sequence", "[xtl][utility]") {
    SECTION("non-empty type list") {
        REQUIRE(test_integer_sequence(xtl::index_sequence_for<char, short, int, long, double>()) == 5);
    }

    SECTION("empty type list") {
        REQUIRE(test_integer_sequence(xtl::index_sequence_for<>()) == 0);
    }
}
