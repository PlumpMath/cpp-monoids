/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/bool_monoid.h"

namespace algebra
{
  namespace detail {
    struct all_traits
    {
      static constexpr bool zero_val() { return true; }
      static constexpr bool append(bool l, bool r) { return l && r; }
    };
  }

  using all = detail::bool_monoid<detail::all_traits>;
}
