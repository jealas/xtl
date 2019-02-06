#pragma once

#include <stddef.h>

namespace xtl {
    template <size_t StartMemoryAddress, size_t EndMemoryAddress, class T>
    struct memory_ptr {
        static_assert(StartMemoryAddress <= EndMemoryAddress);
        static_assert(EndMemoryAddress - StartMemoryAddress + 1== sizeof(T));

        constexpr memory_ptr() noexcept = default;
        ~memory_ptr() noexcept = default;

        memory_ptr(const memory_ptr&) = delete;
        memory_ptr(memory_ptr&&) = delete;

        memory_ptr &operator=(const memory_ptr&) = delete;
        memory_ptr &operator=(memory_ptr&&) = delete;

        constexpr T* get() { return reinterpret_cast<T*>(StartMemoryAddress); }
        constexpr T const * get() const { return reinterpret_cast<T const *>(StartMemoryAddress); }

        constexpr T* operator->() { return get(); }
        constexpr T const * operator->() const { return get(); }

        constexpr T& operator*() noexcept { return *get(); }
        constexpr const T& operator*() const noexcept { return *get(); }
    };

    template <size_t StartMemoryAddress, size_t EndMemoryAddress, class T, size_t N>
    struct memory_ptr<StartMemoryAddress, EndMemoryAddress, T[N]> {
        static_assert(StartMemoryAddress <= EndMemoryAddress);
        static_assert(EndMemoryAddress - StartMemoryAddress + 1 == sizeof(T[N]));

        constexpr memory_ptr() noexcept = default;
        ~memory_ptr() noexcept = default;

        memory_ptr(const memory_ptr&) = delete;
        memory_ptr(memory_ptr&&) = delete;

        memory_ptr &operator=(const memory_ptr&) = delete;
        memory_ptr &operator=(memory_ptr&&) = delete;

        constexpr T* get() { return reinterpret_cast<T*>(StartMemoryAddress); }
        constexpr T const * get() const { return reinterpret_cast<T const *>(StartMemoryAddress); }

        constexpr T* begin() { return get(); }
        constexpr T const * begin() const { return get(); }

        constexpr T* end() { return get() + N; }
        constexpr T const * end() const { return get() + N; }

        constexpr T* operator->() { return get(); }
        constexpr T const * operator->() const { return get(); }

        constexpr T& operator*() noexcept { return *get(); }
        constexpr const T& operator*() const noexcept { return *get(); }

        constexpr T& operator[](const size_t i) noexcept { return *(get() + i); }
        constexpr const T& operator[](const size_t i) const noexcept { return *(get() + i); }
    };

    template <size_t I, size_t StartMemoryAddress, size_t EndMemoryAddress, class T, size_t N>
    constexpr T& get(memory_ptr<StartMemoryAddress, EndMemoryAddress, T[N]> &ptr) {
        static_assert(I < N);
        return ptr[I];
    }

    template <size_t I, size_t StartMemoryAddress, size_t EndMemoryAddress, class T, size_t N>
    constexpr const T& get(const memory_ptr<StartMemoryAddress, EndMemoryAddress, T[N]> &ptr) {
        static_assert(I < N);
        return ptr[I];
    }
}
