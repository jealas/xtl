#include "catch.hpp"

#include <xtl/delegate.h>

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

using predicate = xtl::delegate<bool()>;

TEST_CASE("Test delegate can instantiated", "[xtl][delegate]") {
    SECTION("C++ functions") {
        predicate true_function{true_fn};
        REQUIRE(true_function());

        predicate false_function{false_fn};
        REQUIRE(!false_function());
    }

    SECTION("C functions") {
    }

    SECTION("Class member function") {
        member_fn member;

        predicate true_function{member, &member_fn::true_call};
        REQUIRE(true_function());

        predicate false_function{member, &member_fn::false_call};
        REQUIRE(!false_function());
    }
}

