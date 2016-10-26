/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../../semigroup.h"

#include <type_traits>
#include <utility>

namespace algebra {
  namespace detail {
    enum class MinMax { Min, Max };

    template <typename T, typename Compare, MinMax Op>
    class minmax final
    {
      public:
        using base_type = T;

        constexpr minmax(base_type const& v,
                         Compare less = Compare())
          : _less(less), _v(v) {}
        constexpr minmax(base_type&& v,
                         Compare less = Compare())
          : _less(less), _v(std::move(v)) {}
        constexpr minmax(minmax const&) = default;
        constexpr minmax(minmax&&) = default;

        constexpr minmax& operator=(minmax const&) = default;
        constexpr minmax& operator=(minmax&&) = default;

        constexpr base_type const& value() const {
          return _v;
        }

        constexpr explicit operator base_type() const & {
          return _v;
        }

        constexpr explicit operator base_type() && {
          return std::move(_v);
        }

        constexpr minmax sappend(minmax const& r) const {
          return minmax(minmaxop(r._v));
        }

      private:
        constexpr base_type minmaxop(base_type const& rval) const {
          if (Op == MinMax::Min)
            return std::min(_v, rval, _less);
          return std::max(_v, rval, _less);
        }

        Compare   _less;
        base_type _v;
    };

    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator==(minmax<T, Compare, Op> const& lhs, minmax<T, Compare, Op> const& rhs) {
      return lhs.value() == rhs.value();
    }
    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator==(T const& lhs, minmax<T, Compare, Op> const& rhs) {
      return lhs == rhs.value();
    }
    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator==(minmax<T, Compare, Op> const& lhs, T const& rhs) {
      return lhs.value() == rhs;
    }
    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator!=(minmax<T, Compare, Op> const& lhs, minmax<T, Compare, Op> const& rhs) {
      return lhs.value() != rhs.value();
    }
    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator!=(T const& lhs, minmax<T, Compare, Op> const& rhs) {
      return lhs != rhs.value();
    }
    template <typename T, typename Compare, MinMax Op>
    inline constexpr bool operator!=(minmax<T, Compare, Op> const& lhs, T const& rhs) {
      return lhs.value() != rhs;
    }
  }

  template <typename T, typename Compare, detail::MinMax Op>
  struct is_semigroup<detail::minmax<T, Compare, Op>> : std::true_type {};

  template <typename T, typename Compare, detail::MinMax Op>
  struct semigroup<detail::minmax<T, Compare, Op>>
  {
    using minmax_t = detail::minmax<T, Compare, Op>;
    static constexpr minmax_t append(minmax_t const& a, minmax_t const& b) {
      return a.sappend(b);
    }
  };
}
