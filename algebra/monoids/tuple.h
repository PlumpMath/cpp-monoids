/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"
#include "all.h"

#include <tuple>
#include <type_traits>
#include <utility>

namespace algebra {
  template <typename... TS>
  struct is_semigroup<std::tuple<TS...>>
    : std::conditional_t<
          static_cast<bool>(mconcat({ all(is_semigroup_v<TS>)... })),
          std::true_type,
          std::false_type
        >
  {};

  template <typename... TS>
  struct is_monoid<std::tuple<TS...>>
    : std::conditional_t<
          static_cast<bool>(mconcat({ all(is_monoid_v<TS>)... })),
          std::true_type,
          std::false_type
        >
  {};

  template <typename... TS>
  struct semigroup<std::tuple<TS...>>
  {
    static constexpr std::tuple<TS...> append(std::tuple<TS...> const& a,
                                              std::tuple<TS...> const& b) {
      return int_append(a, b, std::index_sequence_for<TS...>());
    }

    private:
      template <std::size_t... Is>
      static constexpr std::tuple<TS...> int_append(std::tuple<TS...> const& a,
                                                    std::tuple<TS...> const& b,
                                                    std::index_sequence<Is...>) {
        return std::make_tuple(sappend(std::get<Is>(a), std::get<Is>(b))...);
      }
  };

  template <typename... TS>
  struct monoid<std::tuple<TS...>>
    : semigroup<std::tuple<TS...>>
  {
    static constexpr std::tuple<TS...> zero() {
      return std::make_tuple(mzero<TS>()...);
    }
  };
}
