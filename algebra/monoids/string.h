/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"

#include <string>

namespace algebra {
  template <
    typename CharT,
    typename Traits,
    typename Allocator
    >
  struct is_semigroup<std::basic_string<CharT, Traits, Allocator>>
    : std::true_type {};

  template <
    typename CharT,
    typename Traits,
    typename Allocator
    >
  struct is_monoid<std::basic_string<CharT, Traits, Allocator>>
    : std::true_type {};

  template <
    typename CharT,
    typename Traits,
    typename Allocator
    >
  struct semigroup<std::basic_string<CharT, Traits, Allocator>>
  {
    using string_type = std::basic_string<CharT, Traits, Allocator>;

    static constexpr string_type append(string_type const& a, string_type const& b) {
      return a+b;
    }
  };

  template < 
    typename CharT,
    typename Traits,
    typename Allocator
    >
  struct monoid<std::basic_string<CharT, Traits, Allocator>>
    : semigroup<std::basic_string<CharT, Traits, Allocator>>
  {
    using string_type = std::basic_string<CharT, Traits, Allocator>;

    static constexpr string_type zero() {
      return {};
    }
  };
}
