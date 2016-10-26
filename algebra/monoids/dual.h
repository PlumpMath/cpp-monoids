/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../monoid.h"

#include <string>
#include <utility>

namespace algebra {
  template <typename M, typename = std::enable_if_t<is_semigroup_v<M>>>
  class dual final
  {
    public:
      template <typename T = M, typename = std::enable_if_t<is_monoid_v<T>>>
      constexpr dual()
        : _v(mempty<M>())
      {}
      constexpr dual(M m)
        : _v(std::move(m))
      {}
      constexpr dual(dual const&) = default;
      constexpr dual(dual&&) = default;

      constexpr dual& operator=(dual const&) = default;
      constexpr dual& operator=(dual&&) = default;

      constexpr M& operator*() & { return _v; }
      constexpr M operator*() && { return std::move(_v); }
      constexpr M const& operator*() const & { return _v; }
      constexpr M* operator->() { return &_v; }
      constexpr M const* operator->() const { return &_v; }

      constexpr M const& value() const & {
        return _v;
      }

      constexpr M value() const && {
        return std::move(_v);
      }

      constexpr explicit operator M() const & {
        return _v;
      }

      constexpr explicit operator M() && {
        return std::move(_v);
      }

    private:
      M _v;
  };

  template <typename M>
  struct is_semigroup<dual<M>> : is_semigroup_t<M> {};
  template <typename M>
  struct is_monoid<dual<M>> : is_monoid_t<M> {};

  template <typename M>
  struct semigroup<dual<M>>
  {
    static constexpr dual<M> append(dual<M> const& a, dual<M> const& b) {
      return dual<M>(sappend(*b, *a));
    }
  };

  template <typename M>
  struct monoid<dual<M>>
    : semigroup<dual<M>>
  {
    static constexpr dual<M> zero() {
      return {};
    }
  };
}
