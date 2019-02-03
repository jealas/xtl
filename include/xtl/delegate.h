#pragma once

#include <xtl/type_traits.h>


namespace xtl {
    template <class FunctionT>
    class delegate;

    template <class ReturnT, class ... Args>
    class delegate<ReturnT(Args...)> {
    public:
        using type = ReturnT(Args...);

    private:
        struct Void {};

        using function_ptr_t = type*;
        using member_function_ptr_t = ReturnT(Void::*)(Args...);

        union function_t {
            explicit function_t(function_ptr_t fn_ptr) : function_ptr{fn_ptr} {}
            explicit function_t(member_function_ptr_t member_fn_ptr) : member_function_ptr{member_fn_ptr} {}

            function_ptr_t function_ptr;
            member_function_ptr_t member_function_ptr;
        };

        using storage_t = void*;
        using delegate_t = ReturnT(*)(function_t, storage_t, Args...);

    public:
        delegate(ReturnT(*fn)(Args...)) noexcept
            : delegate_{&function_ptr_delegate}, function_{reinterpret_cast<function_ptr_t>(fn)}, storage_{nullptr} {}

        template <class Callable>
        delegate(Callable &callable, ReturnT (Callable::*member_fn)(Args...)) noexcept
            : delegate_{&member_function_ptr_delegate<Callable>}, function_{reinterpret_cast<member_function_ptr_t>(member_fn)}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        template <class Callable, class = enable_if_t<not is_same_v<Callable, delegate<type>>>>
        delegate(Callable &callable) noexcept
            : delegate_{&member_function_ptr_delegate<Callable>}, function_{reinterpret_cast<member_function_ptr_t>(&Callable::operator())}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        delegate(const delegate&) noexcept = default;
        delegate(delegate&&) noexcept = default;

        delegate &operator=(const delegate&) noexcept = default;
        delegate &operator=(delegate&&) noexcept = default;

        ReturnT operator()(Args... args) const {
            return delegate_(function_, storage_, args...);
        }

    private:
        static ReturnT function_ptr_delegate(function_t function, storage_t, Args... args) {
            return reinterpret_cast<ReturnT(*)(Args...)>(function.function_ptr)(args...);
        }

        template <class Callable>
        static ReturnT member_function_ptr_delegate(function_t function, storage_t storage, Args... args) {
            auto *callable_ptr = reinterpret_cast<Callable*>(storage);
            return (callable_ptr->*reinterpret_cast<ReturnT(Callable::*)(Args...)>(function.member_function_ptr))(args...);
        }

        delegate_t delegate_;
        function_t function_;
        storage_t storage_;
    };
}