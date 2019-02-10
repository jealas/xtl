#include "catch.hpp"

#include <algorithm>

#include <xtl/array.h>


TEST_CASE("Default constructed arrays default construct all elements.", "[xtl][array]") {
    xtl::array<int, 5> array{};
    REQUIRE(std::all_of(array.begin(), array.end(), [](auto value) {
        return value == 0;
    }));;
}

TEST_CASE("Arrays compare equally to themselves", "[xtl][array]") {
    xtl::array<int, 5> array{1, 2, 3, 4, 5};
    REQUIRE(std::equal(array.begin(), array.end(), array.begin()));;
}

TEST_CASE("Non initialized elements are default initialized", "[xtl][array]") {
    xtl::array<int, 5> array{1, 2, 3};
    REQUIRE(array[0] == 1);
    REQUIRE(array[1] == 2);
    REQUIRE(array[2] == 3);
    REQUIRE(array[3] == 0);
    REQUIRE(array[4] == 0);
}
