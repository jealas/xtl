#pragma once

#include <stddef.h>

#include <xtl/algorithm.h>
#include <xtl/utility.h>

namespace xtl {
    template <class T, size_t N>
    class array {
        static_assert(N > 0, "Array size cannot be zero");

    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = pointer;
        using const_iterator = const iterator;

        template <class... Ts>
        constexpr array(Ts&&... values) : data_{xtl::forward<Ts>(values)...} {}

        template <size_t I>
        constexpr reference at() noexcept {
            static_assert(I < N, "Array index cannot be greater than or equal to the size.");
            return data_[I];
        }

        template <size_t I>
        constexpr const_reference at() const noexcept {
            static_assert(I < N, "Array index cannot be greater than or equal to the size.");
            return data_[I];
        }

        constexpr reference operator[](const size_t i) noexcept { return data_[i]; };
        constexpr const_reference operator[](const size_t i) const noexcept { return data_[i]; };

        constexpr reference front() noexcept { return data_[0]; }
        constexpr const_reference front() const noexcept { return data_[0]; }

        constexpr reference back() noexcept { return data_[N-1]; }
        constexpr const_reference back() const noexcept { return data_[N-1]; }

        constexpr pointer data() noexcept { return data_; }
        constexpr const_pointer data() const noexcept { return data_; }

        constexpr iterator begin() noexcept { return data(); }
        constexpr iterator begin() const noexcept { return data(); }
        constexpr iterator cbegin() const noexcept { return begin(); }

        constexpr iterator end() noexcept { return data() + N; }
        constexpr iterator end() const noexcept { return data() + N; }
        constexpr iterator cend() const noexcept { return end(); }

        constexpr size_t size() const { return N; }
        constexpr size_t max_size() const { return size(); }

        constexpr void fill(const T &value) noexcept { xtl::fill(begin(), end(), value); }

    private:
        T data_[N];
    };

    template <size_t I, class T, size_t N>
    constexpr T& get(array<T, N> &arr) noexcept { return arr.template at<I>(); }

    template <size_t I, class T, size_t N>
    constexpr const T& get(const array<T, N> &arr) noexcept { return arr.template at<I>(); }
}