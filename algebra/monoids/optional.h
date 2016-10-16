/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"

#include <experimental/optional>

namespace algebra
{
  template <typename T>
  struct is_semigroup<std::experimental::optional<T>> : is_semigroup_t<T> {};
  template <typename T>
  struct is_monoid<std::experimental::optional<T>> : is_semigroup_t<T> {};

  template <typename T>
  struct semigroup<std::experimental::optional<T>>
  {
    static constexpr std::experimental::optional<T> append(std::experimental::optional<T> a, std::experimental::optional<T> b) {
      if (a && b)
        return std::experimental::make_optional(sappend(*a, *b));
      else if (a)
        return a;
      return b;
    }
  };

  template <typename T>
  struct monoid<std::experimental::optional<T>> : semigroup<std::experimental::optional<T>>
  {
    static constexpr std::experimental::optional<T> zero() {
      return std::experimental::optional<T>();
    }
  };
}
