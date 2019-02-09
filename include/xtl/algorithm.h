#pragma once

namespace xtl {
   // Fill
   template <class ForwardIterator, class T>
   constexpr void fill(ForwardIterator begin, ForwardIterator end, const T &value) noexcept {
      while (begin != end) {
         *begin = value;
         ++begin;
      }
   }
}