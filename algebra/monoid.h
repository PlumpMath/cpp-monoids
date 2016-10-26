/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/are_convertible_to.h"
#include "semigroup.h"

#include <initializer_list>
#include <iterator>
#include <type_traits>

namespace algebra
{
  template <typename T>
  struct is_monoid : std::false_type {};

  template <typename T>
  using is_monoid_t = typename is_monoid<T>::type;
  template <typename T>
  constexpr bool is_monoid_v = is_monoid<T>::value;

  template <typename T, typename = std::enable_if_t<is_monoid_v<T>>>
  struct monoid;

  template <typename M, typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M mempty()
  {
    return monoid<M>::zero();
  }

  template <typename M, typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M mappend(M const& l, M const& r)
  {
    return monoid<M>::append(l, r);
  }

  template <typename InputIt,
            typename M = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M maccumulate(InputIt begin, InputIt end, M init = mempty<M>())
  {
    while (begin != end)
      init = mappend(init, *begin++);
    return init;
  }

  template <typename M, typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M mconcat(M const& m)
  {
    return m;
  }

  template <typename M, typename M1, typename... MS,
            typename = std::enable_if_t<
                        is_monoid_v<M> &&
                        detail::are_convertible_to_v<M, M1, MS...>>>
  inline constexpr M mconcat(M const& m, M1 const& m1, MS const&... ms)
  {
    return mappend(m, mconcat<M>(m1, ms...));
  }

  template <typename M, typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M mconcat(std::initializer_list<M> const& ms)
  {
    return maccumulate(ms.begin(), ms.end());
  }

  template <typename InputIt, typename OutputIt,
            typename M = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline OutputIt mpartial_sum(InputIt first, InputIt last, OutputIt out)
  {
    return spartial_sum(first, last, out);
  }

  template <typename InputIt1, typename InputIt2, typename OutputIt,
            typename M = typename std::iterator_traits<InputIt1>::value_type,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline OutputIt mzip(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt out)
  {
    return szip(first1, last1, first2, out);
  }

  template <typename InputIt,
            typename UnaryOp,
            typename M = std::result_of_t<UnaryOp(typename std::iterator_traits<InputIt>::value_type)>,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline M mtransform_accumulate(InputIt first, InputIt last, UnaryOp op, M init = mempty<M>())
  {
    return stransform_accumulate(first, last, op, init);
  }

  template <typename InputIt,
            typename M = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline M mintersperse(InputIt first, InputIt last, M e, M init = mempty<M>())
  {
    return sintersperse(first, last, e, init);
  }

  template <typename InputIt,
            typename M = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_monoid_v<M>>>
  inline constexpr M mreplicate(std::size_t n, M e)
  {
    M res = mempty<M>();
    for (std::size_t i = 0; i < n; ++i)
      res = mappend(res, e);
    return res;
  }
}
