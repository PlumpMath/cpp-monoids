/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/bitset.h"

namespace algebra
{
  namespace detail {
    template <size_t N>
    inline constexpr std::bitset<N> all_bits_value() {
      std::bitset<N> all_bits;
      all_bits.set();
      return all_bits;
    }

    struct bitset_and_traits
    {
      template <size_t N>
      static constexpr std::bitset<N> zero_val() {
        return all_bits_value<N>();
      }

      template <size_t N>
      static constexpr std::bitset<N> append(std::bitset<N> const& a, std::bitset<N> const& b) {
        return a & b;
      }
    };

    struct bitset_or_traits
    {
      template <size_t N>
      static constexpr std::bitset<N> zero_val() {
        return {};
      }

      template <size_t N>
      static constexpr std::bitset<N> append(std::bitset<N> const& a, std::bitset<N> const& b) {
        return a | b;
      }
    };

    struct bitset_xor_traits
    {
      template <size_t N>
      static constexpr std::bitset<N> zero_val() {
        return {};
      }

      template <size_t N>
      static constexpr std::bitset<N> append(std::bitset<N> const& a, std::bitset<N> const& b) {
        return a ^ b;
      }
    };
  }

  template <size_t N>
  using bitset_and = detail::bitset<N, detail::bitset_and_traits>;
  template <size_t N>
  using bitset_or = detail::bitset<N, detail::bitset_or_traits>;
  template <size_t N>
  using bitset_xor = detail::bitset<N, detail::bitset_xor_traits>;
}
