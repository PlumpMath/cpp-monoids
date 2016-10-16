/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "../../monoid.h"

#include <bitset>
#include <type_traits>

namespace algebra
{
  namespace detail {
    template <size_t N, typename Traits>
    class bitset final
      : public std::bitset<N>
    {
      public:
        constexpr bitset() : std::bitset<N>(Traits::template zero_val<N>()) {}
        constexpr bitset(std::bitset<N> const& v) : std::bitset<N>(v) {}
        constexpr explicit bitset(unsigned long long val) : std::bitset<N>(val) {}
        template <typename CharT, typename STraits, typename Alloc>
        explicit bitset(std::basic_string<CharT, STraits, Alloc> const& str,
                        typename std::basic_string<CharT, STraits, Alloc>::size_type pos = 0,
                        typename std::basic_string<CharT, STraits, Alloc>::size_type n =
                          std::basic_string<CharT, STraits, Alloc>::npos,
                        CharT zero = CharT('0'), 
                        CharT one = CharT('1'))
         : std::bitset<N>(str, pos, n, zero, one) 
        {}
        template <typename CharT>
        explicit bitset(CharT const* str,
                        typename std::basic_string<CharT>::size_type n =
                          std::basic_string<CharT>::npos,
                        CharT zero = CharT('0'), 
                        CharT one = CharT('1'))
          : std::bitset<N>(str, n, zero, one)
        {}

        constexpr bitset(bitset const&) = default;
        constexpr bitset& operator=(bitset const&) = default;

        constexpr bitset& operator&=(const bitset& rhs) {
          std::bitset<N>::operator&=(rhs);
          return *this;
        }
        constexpr bitset& operator|=(const bitset& rhs) {
          std::bitset<N>::operator|=(rhs);
          return *this;
        }
        constexpr bitset& operator^=(const bitset& rhs) {
          std::bitset<N>::operator^=(rhs);
          return *this;
        }
        constexpr bitset& operator<<=(size_t pos) {
          std::bitset<N>::operator<<=(pos);
          return *this;
        }
        constexpr bitset& operator>>=(size_t pos) {
          std::bitset<N>::operator>>=(pos);
          return *this;
        }
        constexpr bitset operator~() const {
          return bitset(std::bitset<N>::operator~());
        }
        constexpr bitset operator<<(size_t pos) const {
          return bitset(std::bitset<N>::operator<<(pos));
        }
        constexpr bitset operator>>(size_t pos) const {
          return bitset(std::bitset<N>::operator>>(pos));
        }

        constexpr bitset sappend(bitset const& other) const {
          return bitset(Traits::template append<N>(*this, other));
        }
    };

    template <size_t N, typename Traits>
    inline constexpr bitset<N, Traits> operator&(bitset<N, Traits> const& a, bitset<N, Traits> const& b) {
      return bitset<N, Traits>(static_cast<std::bitset<N>>(a) & static_cast<std::bitset<N>>(b));
    }
    template <size_t N, typename Traits>
    inline constexpr bitset<N, Traits> operator|(bitset<N, Traits> const& a, bitset<N, Traits> const& b) {
      return bitset<N, Traits>(static_cast<std::bitset<N>>(a) | static_cast<std::bitset<N>>(b));
    }
    template <size_t N, typename Traits>
    inline constexpr bitset<N, Traits> operator^(bitset<N, Traits> const& a, bitset<N, Traits> const& b) {
      return bitset<N, Traits>(static_cast<std::bitset<N>>(a) ^ static_cast<std::bitset<N>>(b));
    }
  }

  template <size_t N, typename Traits>
  struct is_semigroup<detail::bitset<N, Traits>> : std::true_type {};
  template <size_t N, typename Traits>
  struct is_monoid<detail::bitset<N, Traits>> : std::true_type {};

  template <size_t N, typename Traits>
  struct semigroup<detail::bitset<N, Traits>>
  {
    static constexpr detail::bitset<N, Traits> append(detail::bitset<N, Traits> const& a, detail::bitset<N, Traits> const& b) {
      return a.sappend(b);
    }
  };

  template <size_t N, typename Traits>
  struct monoid<detail::bitset<N, Traits>> : semigroup<detail::bitset<N, Traits>>
  {
    static constexpr detail::bitset<N, Traits> zero() {
      return {};
    }
  };
}
