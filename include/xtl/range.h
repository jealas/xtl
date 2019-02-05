#pragma once

#include <xtl/iterator.h>

namespace xtl {
    struct begin_iterator_tag {};
    struct end_iterator_tag {};

    template <class T, T Start, T End>
    struct constant_range {
        static_assert(Start <= End, "Constant range start must be <= end.");

        class iterator : public xtl::iterator<forward_iterator_tag, T, T> {
        public:
            constexpr iterator() noexcept : current_{End} {}
            constexpr iterator(begin_iterator_tag) noexcept : current_{Start} {}
            constexpr iterator(end_iterator_tag) noexcept : current_{End} {}

            constexpr iterator(const iterator&) noexcept = default;
            constexpr iterator(iterator&&) noexcept = default;

            constexpr iterator& operator=(const iterator&) noexcept = default;
            constexpr iterator& operator=(iterator&&) noexcept = default;

            constexpr bool operator==(iterator other) const noexcept { return current_ == other.current_; }
            constexpr bool operator!=(iterator other) const noexcept { return current_ != other.current_; }

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

        constexpr iterator begin() const noexcept { return {begin_iterator_tag{}}; }
        constexpr iterator end() const noexcept { return {end_iterator_tag{}}; }
    };

    template <class T, T Start, T End>
    constexpr constant_range<T, Start, End> crange;

    template <int Start, int End>
    constexpr constant_range<int, Start, End> int_crange;

    template <unsigned Start, unsigned End>
    constexpr constant_range<unsigned, Start, End> unsigned_crange;

    template <size_t Start, size_t End>
    constexpr constant_range<size_t, Start, End> size_crange;
}