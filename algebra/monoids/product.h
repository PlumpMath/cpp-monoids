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
    struct product_traits
    {
      using type = T;

      static constexpr T zero_val() { return 1; }
      static constexpr T append(T l, T r) { return l*r; }
    };
  }

  template <typename T>
  using product = detail::num<detail::product_traits<T>>;
}
