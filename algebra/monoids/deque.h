/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"

#include <deque>
#include <type_traits>

namespace algebra {
  template <typename T, typename Allocator>
  struct is_semigroup<std::deque<T, Allocator>> : std::true_type {};
  template <typename T, typename Allocator>
  struct is_monoid<std::deque<T, Allocator>> : std::true_type {};

  template <typename T, typename Allocator>
  struct semigroup<std::deque<T, Allocator>>
  {
    using seq_type = std::deque<T, Allocator>;

    static constexpr seq_type append(seq_type a, seq_type const& b) {
      a.insert(a.end(), b.cbegin(), b.cend());
      return a;
    }
  };

  template <typename T, typename Allocator>
  struct monoid<std::deque<T, Allocator>> : semigroup<std::deque<T, Allocator>>
  {
    static constexpr std::deque<T, Allocator> zero() {
      return {};
    }
  };
}
