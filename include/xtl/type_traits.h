#pragma once

#include <stddef.h>
#include <stdint.h>

#include <xtl/cstddef.h>

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
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

    template <class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;

    // Aligned storage
    template <size_t Size, size_t Alignment = alignof(uint8_t)>
    struct aligned_storage {
        struct type {
            alignas(Alignment) uint8_t data[Size];
        };
    };

    template <size_t Size, size_t Alignment = alignof(uint8_t)>
    using aligned_storage_t = typename aligned_storage<Size, Alignment>::type;

    // Alignment of
    template <class T>
    struct alignment_of : integral_constant<size_t, alignof(T)> {};

    template <class T>
    constexpr auto alignment_of_v = alignment_of<T>::value;

    // Remove const
    template <class T>
    struct remove_const { using type = T; };

    template <class T>
    struct remove_const<const T> { using type = T; };

    template <class T>
    using remove_const_t = typename remove_const<T>::type;

    // Add const
    template <class T>
    struct add_const { using type = const T; };

    template <class T>
    using add_const_t = typename add_const<T>::type;

    // Remove volatile
    template <class T>
    struct remove_volatile { using type = T; };

    template <class T>
    struct remove_volatile<volatile T> { using type = T; };

    template <class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    // Add volatile
    template <class T>
    struct add_volatile { using type = volatile T; };

    template <class T>
    using add_volatile_t = typename add_volatile<T>::type;

    // Remove const and volatile
    template <class T>
    struct remove_cv { using type = remove_volatile_t<remove_const_t<T>>; };

    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;

    // Add const and volatile
    template <class T>
    struct add_cv { using type = add_const_t<add_volatile_t<T>>; };

    template <class T>
    using add_cv_t = typename add_cv<T>::type;

    // Remove reference
    template <class T>
    struct remove_reference { using type = T; };

    template <class T>
    struct remove_reference<T&> { using type = T; };

    template <class T>
    struct remove_reference<T&&> { using type = T; };

    template <class T>
    using remove_reference_t = typename remove_reference<T>::type;

    // Remove const, volatile and reference
    template <class T>
    struct remove_cvref { using type = remove_cv_t<remove_reference_t<T>>; };

    template <class T>
    using remove_cvref_t = typename remove_cvref<T>::type;

    // Add pointer
    template <class T>
    struct add_pointer { using type = T*; };

    template <class T>
    using add_pointer_t = typename add_pointer<T>::type;

    // Remove pointer
    template <class T>
    struct remove_pointer { using type = T; };

    template <class T>
    struct remove_pointer<T*> { using type = T; };

    template <class T>
    using remove_pointer_t = typename remove_pointer<T>::type;

    // Void
    template<typename...> struct make_void { using type = void; };
    template<typename... Ts> using void_t = typename make_void<Ts...>::type;

    // Conditional
    template <bool B, class T, class F>
    struct conditional { using type = T; };

    template <class T, class F>
    struct conditional<false, T, F> { using type = F; };

    template <bool B, class T, class F>
    using conditional_t = typename conditional<B, T, F>::type;

    // Remove extent
    template <class T>
    struct remove_extent { using type = T; };

    template <class T>
    struct remove_extent<T[]> { using type = T; };

    template <class T, size_t N>
    struct remove_extent<T[N]> { using type = T; };

    template <class T>
    using remove_extent_t = typename remove_extent<T>::type;

    // Remove all extents
    template <class T>
    struct remove_all_extents { using type = T; };

    template <class T>
    struct remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };

    template <class T, size_t N>
    struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };

    template <class T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;

    // Is void
    template <class T>
    struct is_void : is_same<void, remove_cv_t<T>> {};

    template <class T>
    constexpr bool is_void_v = is_void<T>::value;

    // Is null pointer
    template <class T>
    struct is_null_pointer : is_same<xtl::nullptr_t, remove_cv_t<T>> {};

    template <class T>
    constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

    // Is l-value reference
    template <class T>
    struct is_lvalue_reference : false_type {};

    template <class T>
    struct is_lvalue_reference<T&> : true_type {};

    template <class T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
}