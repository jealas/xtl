#include "catch.hpp"

#include <memory>

#include <xtl/delegate.h>

using predicate = xtl::delegate<bool()>;

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

struct callable {
    bool value;

    bool operator()() const {
        return value;
    }
};

extern "C" bool true_c_fn() {
    return true;
}

extern "C" bool false_c_fn() {
    return false;
}

struct virtual_callable {
    virtual bool operator()() = 0;
};

struct virtual_true_callable : virtual_callable {
    bool operator()() override {
        return true;
    }
};

struct virtual_false_callable : virtual_callable {
    bool operator()() override {
        return false;
    }
};

TEST_CASE("Delegate can instantiated", "[xtl][delegate]") {
    SECTION("C++ functions") {
        predicate true_function{true_fn};
        REQUIRE(true_function());

        predicate false_function{false_fn};
        REQUIRE(!false_function());
    }

    SECTION("C functions") {
        predicate true_function{true_c_fn};
        REQUIRE(true_function());

        predicate false_function{false_c_fn};
        REQUIRE(!false_function());
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

    SECTION("Virtual callable call") {
        std::unique_ptr<virtual_callable> virtual_true_function{new virtual_true_callable()};
        predicate true_function{*virtual_true_function};

        REQUIRE(true_function());

        std::unique_ptr<virtual_callable> virtual_false_function{new virtual_false_callable()};
        predicate false_function{*virtual_false_function};

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

    SECTION("Function pointer from lambda") {
        predicate true_function{+[]() { return true; }};
        REQUIRE(true_function());

        predicate false_function{+[]() { return false; }};
        REQUIRE(!false_function());
    }
}

TEST_CASE("Delegate can be copied", "[xtl][delegate]") {
     SECTION("C++ functions") {
        predicate true_function{true_fn};
        predicate true_function_copy{true_function};
        REQUIRE(true_function_copy());
        REQUIRE(true_function());

        predicate false_function{false_fn};
        predicate false_function_copy{false_fn};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("C functions") {
        predicate true_function{true_c_fn};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        predicate false_function{false_c_fn};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("Class member function") {
        member_fn member;

        predicate true_function{member, &member_fn::true_call};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        predicate false_function{member, &member_fn::false_call};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("Callable class") {
        callable true_callable{true};
        predicate true_function{true_callable};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        callable false_callable{false};
        predicate false_function{false_callable};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("Virtual callable call") {
        std::unique_ptr<virtual_callable> virtual_true_function{new virtual_true_callable()};
        predicate true_function{*virtual_true_function};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        std::unique_ptr<virtual_callable> virtual_false_function{new virtual_false_callable()};
        predicate false_function{*virtual_false_function};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("Lambda") {
        const auto t = true;
        auto true_lambda = [&]() { return t; };
        predicate true_function{true_lambda};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        const auto f = false;
        auto false_lambda = [&]() { return f; };
        predicate false_function{false_lambda};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }

    SECTION("Function pointer from lambda") {
        predicate true_function{+[]() { return true; }};
        predicate true_function_copy{true_function};
        REQUIRE(true_function());
        REQUIRE(true_function_copy());

        predicate false_function{+[]() { return false; }};
        predicate false_function_copy{false_function};
        REQUIRE(!false_function());
        REQUIRE(!false_function_copy());
    }
}