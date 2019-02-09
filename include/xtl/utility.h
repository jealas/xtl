#pragma once

#include <stddef.h>

#include <xtl/type_traits.h>


namespace xtl {
    template <class T, T ... Ints>
    struct integer_sequence {
        static constexpr size_t size() noexcept { return sizeof...(Ints); }
    };

    template <size_t... Indexes>
    using index_sequence = integer_sequence<size_t, Indexes...>;

    namespace detail {
        template <class T, T I, T N, T... CurrentSequence>
        struct integer_sequence_builder {
            static_assert(N >= 0, "N should never be < 0");

            using type = typename integer_sequence_builder<T, I + 1, N, CurrentSequence..., I>::type;
        };

        template <class T, T N, T... CurrentSequence>
        struct integer_sequence_builder<T, N, N, CurrentSequence...> {
            using type = integer_sequence<T, CurrentSequence...>;
        };
    }

    template <class T, T N>
    using make_integer_sequence = typename detail::integer_sequence_builder<T, 0, N>::type;

    template <size_t N>
    using make_index_sequence = make_integer_sequence<size_t, N>;

    template <class... Ts>
    using index_sequence_for = make_index_sequence<sizeof...(Ts)>;
}