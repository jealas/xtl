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

struct callable {
    bool value;

    bool operator()() const {
        return value;
    }
};

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

    SECTION("Callable class") {
        callable true_callable{true};
        predicate true_function{true_callable};

        REQUIRE(true_function());

        callable false_callable{false};
        predicate false_function{false_callable};

        REQUIRE(!false_function());
    }

    SECTION("Lambda") {
        const auto t = true;
        auto true_lambda = [&]() { return t; };

        predicate true_function{true_lambda};
        REQUIRE(true_function());

        const auto f = false;
        auto false_lambda = [&]() { return f; };

        predicate false_function{false_lambda};
        REQUIRE(!false_function());
    }
}

