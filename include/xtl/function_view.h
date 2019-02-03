#pragma once

#include <xtl/aligned_storage.h>

namespace xtl {
    template <class FunctionT>
    class function_view;

    template <class ReturnT, class ... Args>
    class function_view<ReturnT(Args...)> {

        struct Void {
        };

        typedef ReturnT(*function_ptr_t)(Args...);
        typedef ReturnT(Void::*member_function_ptr_t)();

        union function_t {
            explicit function_t(function_ptr_t fn_ptr) : function_ptr{fn_ptr} {}
            explicit function_t(member_function_ptr_t member_fn_ptr) : member_function_ptr{member_fn_ptr} {}

            function_ptr_t function_ptr;
            member_function_ptr_t member_function_ptr;
        };

        using storage_t = void*;
        typedef ReturnT(*delegate_t)(function_t, storage_t, Args...);

    public:
        function_view(ReturnT(*fn)(Args...))
            : delegate_{make_delegate(fn)}, function_{reinterpret_cast<function_ptr_t>(fn)}, storage_{nullptr} {}

        template <class Callable>
        function_view(ReturnT (Callable::*member_fn)(Args...), Callable &callable)
            : delegate_{make_delegate(member_fn)}, function_{reinterpret_cast<member_function_ptr_t>(member_fn)}, storage_{reinterpret_cast<storage_t>(&callable)} {}

        ReturnT operator()(Args... args) const {
            return delegate_(function_, storage_, args...);
        }

    private:
        delegate_t make_delegate(ReturnT(*)(Args...)) {
            return +[](function_t function, storage_t, Args... args) -> ReturnT {
                return reinterpret_cast<ReturnT(*)(Args...)>(function.function_ptr)(args...);
            };
        }

        template <class Callable>
        delegate_t make_delegate(ReturnT (Callable::*)(Args...)) {
            return +[](function_t function, storage_t storage, Args... args) {
                auto *callable_ptr = reinterpret_cast<Callable*>(storage);
                return (callable_ptr->*reinterpret_cast<ReturnT(Callable::*)(Args...)>(function.member_function_ptr))(args...);
            };
        }

        delegate_t delegate_;
        function_t function_;
        storage_t storage_;
    };

}