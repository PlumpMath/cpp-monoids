/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include <tuple>
#include <type_traits>

namespace algebra {
  namespace detail {
    template <typename T, typename... TS>
    struct are_same : std::is_same<std::tuple<T, TS...>, std::tuple<TS..., T>> {};
    template <typename T, typename... TS>
    using are_same_t = typename are_same<T, TS...>::type;
    template <typename T, typename... TS>
    constexpr bool are_same_v = are_same<T, TS...>::value;
  }
}
