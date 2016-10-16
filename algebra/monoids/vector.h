/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"

#include <vector>
#include <type_traits>

namespace algebra {
  template <typename T, typename Allocator>
  struct is_semigroup<std::vector<T, Allocator>> : std::true_type {};
  template <typename T, typename Allocator>
  struct is_monoid<std::vector<T, Allocator>> : std::true_type {};

  template <typename T, typename Allocator>
  struct semigroup<std::vector<T, Allocator>>
  {
    using seq_type = std::vector<T, Allocator>;

    static constexpr seq_type append(seq_type a, seq_type const& b) {
      a.insert(a.end(), b.cbegin(), b.cend());
      return a;
    }
  };

  template <typename T, typename Allocator>
  struct monoid<std::vector<T, Allocator>> : semigroup<std::vector<T, Allocator>>
  {
    static constexpr std::vector<T, Allocator> zero() {
      return {};
    }
  };
}
