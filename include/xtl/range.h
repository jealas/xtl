#pragma once

#include <xtl/iterator.h>

namespace xtl {
    struct begin_iterator_tag {};
    struct end_iterator_tag {};

    template <class T, T Begin, T End>
    class constant_range_iterator : public iterator<forward_iterator_tag, T, T> {
    public:
        constexpr constant_range_iterator() noexcept : current_{End} {}
        constexpr constant_range_iterator(begin_iterator_tag) noexcept : current_{Begin} {}
        constexpr constant_range_iterator(end_iterator_tag) noexcept : current_{End} {}

        constexpr constant_range_iterator(const constant_range_iterator&) noexcept = default;
        constexpr constant_range_iterator(constant_range_iterator&&) noexcept = default;

        constexpr constant_range_iterator& operator=(const constant_range_iterator&) noexcept = default;
        constexpr constant_range_iterator& operator=(constant_range_iterator&&) noexcept = default;

        constexpr bool operator==(constant_range_iterator other) const noexcept { return current_ == other.current_; }
        constexpr bool operator!=(constant_range_iterator other) const noexcept { return current_ != other.current_; }

        constexpr const T& operator*() const noexcept { return current_; }

        constexpr T& operator++() noexcept {
            if (current_ != End) {
                ++current_;
            }
            return current_;
        }

        constexpr const T operator++(int) noexcept { return current_ ? current_ == End : current_++; }

        constexpr T& operator--() noexcept {
            if (current_ != End) {
                ++current_;
            }
            return current_;
        }

        constexpr const T operator--(int) noexcept { return current_ ? current_ == End : current_--; }

    private:
        T current_;
    };

    template <class T, T Start, T End>
    struct constant_range {
        static_assert(Start <= End, "Constant range start must be <= end.");

        constexpr constant_range_iterator<T, Start, End> begin() const noexcept { return {begin_iterator_tag{}}; }
        constexpr constant_range_iterator<T, Start, End> end() const noexcept { return {end_iterator_tag{}}; }
    };

    template <class T, T Start, T End>
    constexpr constant_range<T, Start, End> range;

    template <int Start, int End>
    constexpr constant_range<int, Start, End> int_range;

    template <unsigned Start, unsigned End>
    constexpr constant_range<unsigned, Start, End> unsigned_range;

    template <size_t Start, size_t End>
    constexpr constant_range<size_t, Start, End> size_range;
}