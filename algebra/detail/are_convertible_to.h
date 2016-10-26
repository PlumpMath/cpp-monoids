/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include <type_traits>

namespace algebra {
  namespace detail {
    template <typename T, typename... TS>
    struct are_convertible_to : std::true_type {};
    template <typename T, typename T1, typename... TS>
    struct are_convertible_to<T, T1, TS...>
      : std::integral_constant<bool,
                               std::is_convertible<T1, T>::value &&
                                  are_convertible_to<T, TS...>::value>
    {};
    template <typename T, typename... TS>
    using are_convertible_to_t = typename are_convertible_to<T, TS...>::type;
    template <typename T, typename... TS>
    constexpr bool are_convertible_to_v = are_convertible_to<T, TS...>::value;
  }
}
