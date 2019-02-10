#pragma once

#include <xtl/type_traits.h>
#include <xtl/utility.h>


namespace xtl {
    template <class FunctionT>
    class delegate;

    template <class ReturnT, class ... Args>
    class delegate<ReturnT(Args...)> {
    public:
        using type = ReturnT(Args...);

    private:
        using storage_t = void*;
        using delegate_t = ReturnT(*)(storage_t, Args...);
        using function_ptr_t = type*;

        union function_t {
            constexpr explicit function_t(function_ptr_t fn_ptr) : function_ptr{fn_ptr} {}
            constexpr explicit function_t(delegate_t d_ptr) : delegate_ptr{d_ptr} {}

            function_ptr_t function_ptr;
            delegate_t delegate_ptr;
        };

    public:
        constexpr delegate(ReturnT(*fn)(Args...)) noexcept
            : function_{fn}, storage_{nullptr} {}

        template <class Callable, ReturnT(Callable::*MemberFunctionPtr)(Args...)>
        static delegate<type> make(Callable &callable) {
            return {callable, &member_function_ptr_delegate<Callable, MemberFunctionPtr>};
        }

        template <class Callable, ReturnT(Callable::*MemberFunctionPtr)(Args...) const>
        static delegate<type> make(Callable &callable) {
            return {callable, &member_function_ptr_delegate<Callable, MemberFunctionPtr>};
        }

        template <class Callable, class = enable_if_t<not is_same_v<Callable, delegate<type>>>>
        constexpr delegate(Callable &callable) noexcept : delegate{callable, &member_function_ptr_delegate<Callable, &Callable::operator()>} {}

        constexpr delegate(const delegate&) noexcept = default;
        constexpr delegate(delegate&&) noexcept = default;

        constexpr delegate &operator=(const delegate&) noexcept = default;
        constexpr delegate &operator=(delegate&&) noexcept = default;

        constexpr ReturnT operator()(Args&&... args) const {
            if (!storage_) {
                return function_.function_ptr(xtl::forward<Args>(args)...);
            }
            return function_.delegate_ptr(storage_, xtl::forward<Args>(args)...);
        }

    private:
        template <class Callable>
        constexpr delegate(Callable &callable, delegate_t delegate) noexcept
                : function_{delegate}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        template <class Callable, ReturnT(Callable::*MemberFunctionPtr)(Args...)>
        constexpr static ReturnT member_function_ptr_delegate(storage_t storage, Args&&... args) {
            auto *callable_ptr = reinterpret_cast<Callable*>(storage);
            return (callable_ptr->*MemberFunctionPtr)(xtl::forward<Args>(args)...);
        }

        template <class Callable, ReturnT(Callable::*MemberFunctionPtr)(Args...) const>
        constexpr static ReturnT member_function_ptr_delegate(storage_t storage, Args&&... args) {
            auto *callable_ptr = reinterpret_cast<Callable*>(storage);
            return (callable_ptr->*MemberFunctionPtr)(xtl::forward<Args>(args)...);
        }

        function_t function_;
        storage_t storage_;
    };
}