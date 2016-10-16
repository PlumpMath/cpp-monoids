/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/minmax.h"

#include <functional>

namespace algebra {
  template <typename T, typename Compare = std::less<T>>
  using min = detail::minmax<T, Compare, detail::MinMax::Min>;
}
