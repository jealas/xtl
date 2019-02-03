#pragma once

namespace xtl {
    // Enable if
    template <bool, class = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> { using type = T; };

    template <bool B, class T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    // Integral constant
    template <class T, T Value>
    struct integral_constant {
        static constexpr T value = Value;
        using value_type = T;
        using type = integral_constant<T, Value>;

        constexpr operator T() const noexcept { return Value; }
        constexpr T operator()() const noexcept { return Value; }
    };

    // Bool constant
    template <bool Value>
    using bool_constant = integral_constant<bool, Value>;

    // True and false types
    struct true_type : bool_constant<true> {};
    struct false_type : bool_constant<false> {};

    // Is same
    template <class, class>
    struct is_same;

    template <class T, class U>
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

    template <class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;

    // Aligned storage
    template <unsigned char Alignment, unsigned long long Size>
    struct aligned_storage {
        struct type {
            alignas(Alignment) unsigned char data[Size];
        };
    };
}