#include "catch.hpp"

#include <xtl/function_view.h>

bool true_fn() {
    return true;
}

bool false_fn() {
    return false;
}

struct member_fn {
    bool true_call() { return true; }
    bool false_call() { return false; }
};

TEST_CASE("Test function view can instantiated", "[xtl][function_view]") {
    SECTION("C++ functions") {
        xtl::function_view<bool()> true_function{true_fn};
        REQUIRE(true_function());

        xtl::function_view<bool()> false_function{false_fn};
        REQUIRE(!false_function());
    }

    SECTION("C functions") {
    }

    SECTION("Class member function") {
        member_fn true_call;

        xtl::function_view<bool()> true_function{&member_fn::true_call, true_call};
        REQUIRE(true_function());
    }
}

