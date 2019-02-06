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

        constexpr T* data() { return reinterpret_cast<T*>(StartMemoryAddress); }
        constexpr T const * data() const { return reinterpret_cast<T*>(StartMemoryAddress); }

        constexpr T* operator->() { return data(); }
        constexpr T const * operator->() const { return data(); }

        constexpr T& operator*() noexcept { return *data(); }
        constexpr const T& operator*() const noexcept { return *data(); }
    };

    template <size_t StartMemoryAddress, size_t EndMemoryAddress, size_t N, class T>
    struct memory_ptr<StartMemoryAddress, EndMemoryAddress, T[N]> {
        static_assert(StartMemoryAddress <= EndMemoryAddress);
        static_assert(EndMemoryAddress - StartMemoryAddress + 1 == sizeof(T[N]));

        constexpr memory_ptr() noexcept = default;
        ~memory_ptr() noexcept = default;

        memory_ptr(const memory_ptr&) = delete;
        memory_ptr(memory_ptr&&) = delete;

        memory_ptr &operator=(const memory_ptr&) = delete;
        memory_ptr &operator=(memory_ptr&&) = delete;

        constexpr T* data() { return reinterpret_cast<T*>(StartMemoryAddress); }
        constexpr T const * data() const { return reinterpret_cast<T const *>(StartMemoryAddress); }

        constexpr T* begin() { return data(); }
        constexpr T const * begin() const { return data(); }

        constexpr T* end() { return data() + N; }
        constexpr T const * end() const { return data() + N; }

        constexpr T* operator->() { return data(); }
        constexpr T const * operator->() const { return data(); }

        constexpr T& operator*() noexcept { return *data(); }
        constexpr const T& operator*() const noexcept { return *data(); }

        constexpr T& operator[](const size_t i) noexcept { return *(data() + i); }
        constexpr const T& operator[](const size_t i) const noexcept { return *(data() + i); }
    };
}
