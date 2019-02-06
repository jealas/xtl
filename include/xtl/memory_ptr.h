#pragma once

#include <stddef.h>

namespace xtl {
    template <size_t MemoryAddress, class T>
    struct memory_ptr {
        ~memory_ptr() noexcept { this->~T(); }
        memory_ptr() noexcept { this->T(); }

        template <class ... Args>
        memory_ptr(Args && ... args) noexcept { this->T(args...); }

        T& operator*() noexcept { return *reinterpret_cast<T*>(MemoryAddress); }
        const T& operator*() const noexcept { return *reinterpret_cast<T*>(MemoryAddress); }
    };
}