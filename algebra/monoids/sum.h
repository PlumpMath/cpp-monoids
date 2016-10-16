/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/num.h"

namespace algebra {
  namespace detail {
    template <typename T>
    struct sum_traits
    {
      using type = T;

      static constexpr T zero_val() { return 0; }
      static constexpr T append(T l, T r) { return l+r; }
    };
  }

  template <typename T>
  using sum = detail::num<detail::sum_traits<T>>;
}
