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
            constexpr explicit function_t(function_ptr_t fn_ptr) : function_ptr{fn_ptr} {}
            constexpr explicit function_t(member_function_ptr_t member_fn_ptr) : member_function_ptr{member_fn_ptr} {}

            function_ptr_t function_ptr;
            member_function_ptr_t member_function_ptr;
        };

        using storage_t = void*;
        using delegate_t = ReturnT(*)(function_t, storage_t, Args...);

    public:
        constexpr delegate(ReturnT(*fn)(Args...)) noexcept
            : delegate_{nullptr}, function_{fn}, storage_{nullptr} {}

        template <class Callable>
        constexpr delegate(Callable &callable, ReturnT (Callable::*member_fn)(Args...)) noexcept
            : delegate_{&member_function_ptr_delegate<Callable>}, function_{reinterpret_cast<member_function_ptr_t>(member_fn)}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        template <class Callable, class = enable_if_t<not is_same_v<Callable, delegate<type>>>>
        constexpr delegate(Callable &callable) noexcept
            : delegate_{&member_function_ptr_delegate<Callable>}, function_{reinterpret_cast<member_function_ptr_t>(&Callable::operator())}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        constexpr delegate(const delegate&) noexcept = default;
        constexpr delegate(delegate&&) noexcept = default;

        constexpr delegate &operator=(const delegate&) noexcept = default;
        constexpr delegate &operator=(delegate&&) noexcept = default;

        constexpr ReturnT operator()(Args... args) const {
            if (!delegate_) {
                return function_.function_ptr(args...);
            }
            return delegate_(function_, storage_, args...);
        }

    private:
        template <class Callable>
        constexpr static ReturnT member_function_ptr_delegate(function_t function, storage_t storage, Args... args) {
            static_assert(sizeof(ReturnT(Void::*)(Args...)) == sizeof(ReturnT(Callable::*)(Args...)),
                    "This compiler is non-standards compliant and pointers to member functions are not guaranteed to be the same size for all types.");

            auto *callable_ptr = reinterpret_cast<Callable*>(storage);
            return (callable_ptr->*reinterpret_cast<ReturnT(Callable::*)(Args...)>(function.member_function_ptr))(args...);
        }

        delegate_t delegate_;
        function_t function_;
        storage_t storage_;
    };
}