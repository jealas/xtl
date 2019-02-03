#pragma once

namespace xtl {
    // Enable if
    template <bool, class = void>
    struct enable_if;

    template <class T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <class T>
    struct enable_if<false, T> {
    };

    // Integral constant
    template <class T, T Value>
    struct integral_constant {
        static constexpr T value = Value;
        using value_type = T;
        using type = integral_constant<T, Value>;

        constexpr operator T() const noexcept { return Value; }
        constexpr T operator()() const noexcept { return Value; }
    };

    // True and false types
    struct true_type : integral_constant<bool, true> {};
    struct false_type : integral_constant<bool, false> {};

    // Is same
    template <class, class>
    struct is_same;

    template <class T, class U>
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

}