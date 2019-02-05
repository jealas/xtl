#pragma once

#include <stddef.h>

#include <xtl/type_traits.h>


namespace xtl {
    // Iterator tags
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    // Iterator helper
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    // Iterator traits
    template <class Iterator>
    struct iterator_traits {
        using difference_type = typename Iterator::difference_type;
        using value_type = typename Iterator::value_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
        using iterator_category = typename Iterator::iterator_category;
    };

    template <class T>
    struct iterator_traits<T*> {
        using difference_type = ptrdiff_t;
        using value_type = remove_cv_t<T>;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;
    };

    // Begin
    template <class Container>
    constexpr auto begin (Container& c) noexcept -> decltype(c.begin()) { return c.begin(); }

    template <class Container>
    constexpr auto begin (const Container& c) noexcept -> decltype(c.begin()) { return c.begin(); }

    template <class T, size_t N>
    constexpr T* begin (T(&array)[N]) noexcept {
        static_assert(N > 0, "Can only get the beginning of an array with more than 0 elements.");
        return &array[0];
    }

    template <class Container>
    constexpr auto cbegin(const Container& c) noexcept -> decltype(begin(c)) { return begin(c); }

    // End
    template <class Container>
    constexpr auto end (Container& c) noexcept -> decltype(c.end()) { return c.end(); }

    template <class Container>
    constexpr auto end (const Container& c) noexcept -> decltype(c.end()) { return c.end(); }

    template <class T, size_t N>
    constexpr T* end (T(&array)[N]) noexcept {
        static_assert(N > 0, "Can only get the end of an array with more than 0 elements.");
        return &array[N];
    }

    template <class T, size_t N>
    constexpr T const * end (const T(&array)[N]) noexcept {
        static_assert(N > 0, "Can only get the end of an array with more than 0 elements.");
        return &array[N];
    }

    template <class Container>
    constexpr auto cend(const Container &c) noexcept -> decltype(end(c)) { return end(c); }

    // Size
    template <class Container>
    constexpr auto size(const Container& c) noexcept -> decltype(c.size()) { return c.size(); }

    template <class T, size_t N>
    constexpr size_t size(const T(&)[N]) noexcept {
        return N;
    }

    // Data
    template <class Container>
    constexpr auto data(Container &c) noexcept -> decltype(c.data()) { return c.data(); }

    template <class Container>
    constexpr auto data(const Container &c) noexcept -> decltype(c.data()) { return c.data(); }

    template <class T, size_t N>
    constexpr T* data(T(&array)[N]) {
        static_assert(N > 0, "Can only get the data for an array with more than 0 elements.");
        return &array[0];
    }

    template <class T, size_t N>
    constexpr T const * data(const T(&array)[N]) {
        static_assert(N > 0, "Can only get the data for an array with more than 0 elements.");
        return &array[0];
    }
}