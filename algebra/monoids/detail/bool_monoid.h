/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../../monoid.h"

#include <type_traits>

namespace algebra
{
  namespace detail {
    template <typename Traits>
    class bool_monoid final
    {
      public:
        constexpr bool_monoid() : _v(Traits::zero_val()) {}
        constexpr bool_monoid(bool v) : _v(v) {}
        constexpr bool_monoid(bool_monoid const&) = default;

        constexpr bool_monoid& operator=(bool_monoid const&) = default;

        constexpr bool value() const {
          return _v;
        }

        constexpr explicit operator bool() const {
          return _v;
        }

        constexpr bool_monoid sappend(bool_monoid other) const {
          return bool_monoid(Traits::append(_v, other._v));
        }

      private:
        bool _v;
    };

    template <typename Traits>
    inline constexpr bool_monoid<Traits> operator&&(bool_monoid<Traits> lhs, bool_monoid<Traits> rhs) {
      return bool_monoid<Traits>(static_cast<bool>(lhs) && static_cast<bool>(rhs));
    }
    template <typename Traits>
    inline constexpr bool_monoid<Traits> operator||(bool_monoid<Traits> lhs, bool_monoid<Traits> rhs) {
      return bool_monoid<Traits>(static_cast<bool>(lhs) || static_cast<bool>(rhs));
    }
  }

  template <typename Traits>
  struct is_semigroup<detail::bool_monoid<Traits>> : std::true_type {};
  template <typename Traits>
  struct is_monoid<detail::bool_monoid<Traits>> : std::true_type {};

  template <typename Traits>
  struct semigroup<detail::bool_monoid<Traits>>
  {
    static constexpr detail::bool_monoid<Traits> append(detail::bool_monoid<Traits> a, detail::bool_monoid<Traits> b) {
      return a.sappend(b);
    }
  };

  template <typename Traits>
  struct monoid<detail::bool_monoid<Traits>> : semigroup<detail::bool_monoid<Traits>>
  {
    static constexpr detail::bool_monoid<Traits> zero() {
      return detail::bool_monoid<Traits>();
    }
  };
}
