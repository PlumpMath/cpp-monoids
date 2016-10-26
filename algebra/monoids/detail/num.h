/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../../monoid.h"

#include <type_traits>

namespace algebra {
  namespace detail {
    template <typename Traits>
    class num final
    {
      public:
        using num_type = typename Traits::type;

        constexpr num() : _v(Traits::zero_val()) {}
        constexpr num(num_type v) : _v(v) {}
        constexpr num(num const&) = default;
        constexpr num(num&&) = default;

        constexpr num& operator=(num const&) = default;
        constexpr num& operator=(num&&) = default;

        constexpr explicit operator num_type() const {
          return _v;
        }

        constexpr num sappend(num r) const {
          return num(Traits::append(_v, r._v));
        }

      private:
        num_type _v;
    };

    template <typename Traits>
    inline constexpr num<Traits> operator+(num<Traits> lhs, num<Traits> rhs) {
      return num<Traits>(static_cast<typename Traits::type>(lhs) + static_cast<typename Traits::type>(rhs));
    }
    template <typename Traits>
    inline constexpr num<Traits> operator-(num<Traits> lhs, num<Traits> rhs) {
      return num<Traits>(static_cast<typename Traits::type>(lhs) - static_cast<typename Traits::type>(rhs));
    }
    template <typename Traits>
    inline constexpr num<Traits> operator*(num<Traits> lhs, num<Traits> rhs) {
      return num<Traits>(static_cast<typename Traits::type>(lhs) * static_cast<typename Traits::type>(rhs));
    }
    template <typename Traits>
    inline constexpr num<Traits> operator/(num<Traits> lhs, num<Traits> rhs) {
      return num<Traits>(static_cast<typename Traits::type>(lhs) / static_cast<typename Traits::type>(rhs));
    }
    template <typename Traits>
    inline constexpr num<Traits> operator%(num<Traits> lhs, num<Traits> rhs) {
      return num<Traits>(static_cast<typename Traits::type>(lhs) % static_cast<typename Traits::type>(rhs));
    }
    template <typename Traits>
    inline constexpr bool operator==(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) == static_cast<typename Traits::type>(rhs);
    }
    template <typename Traits>
    inline constexpr bool operator!=(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) != static_cast<typename Traits::type>(rhs);
    }
    template <typename Traits>
    inline constexpr bool operator<(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) < static_cast<typename Traits::type>(rhs);
    }
    template <typename Traits>
    inline constexpr bool operator<=(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) <= static_cast<typename Traits::type>(rhs);
    }
    template <typename Traits>
    inline constexpr bool operator>(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) > static_cast<typename Traits::type>(rhs);
    }
    template <typename Traits>
    inline constexpr bool operator>=(num<Traits> lhs, num<Traits> rhs) {
      return static_cast<typename Traits::type>(lhs) >= static_cast<typename Traits::type>(rhs);
    }
  }

  template <typename Traits>
  struct is_semigroup<detail::num<Traits>> : std::is_integral<typename Traits::type> {};
  template <typename Traits>
  struct is_monoid<detail::num<Traits>> : std::is_integral<typename Traits::type> {};

  template <typename Traits>
  struct semigroup<detail::num<Traits>>
  {
    static constexpr detail::num<Traits> append(detail::num<Traits> a, detail::num<Traits> b) {
      return a.sappend(b);
    }
  };

  template <typename Traits>
  struct monoid<detail::num<Traits>> : semigroup<detail::num<Traits>>
  {
    static constexpr detail::num<Traits> zero() {
      return detail::num<Traits>();
    }
  };
}
