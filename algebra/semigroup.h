/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include "detail/are_same.h"

#include <iterator>
#include <type_traits>

namespace algebra
{
  template <typename T>
  struct is_semigroup : std::false_type {};

  template <typename T>
  using is_semigroup_t = typename is_semigroup<T>::type;
  template <typename T>
  constexpr bool is_semigroup_v = is_semigroup<T>::value;

  template <typename T, typename = std::enable_if_t<is_semigroup_v<T>>>
  struct semigroup;

  template <typename S, typename = std::enable_if_t<is_semigroup_v<S>>>
  inline constexpr S sappend(S const& l, S const& r)
  {
    return semigroup<S>::append(l, r);
  }

  template <typename InputIt,
            typename S = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_semigroup_v<S>>>
  inline constexpr S saccumulate(InputIt first, InputIt last, S init)
  {
    while (first != last)
      init = sappend(init, *first++);
    return init;
  }

  template <typename S, typename = std::enable_if_t<is_semigroup_v<S>>>
  inline constexpr S sconcat(S const& s)
  {
    return s;
  }

  template <typename S, typename S1, typename... SS,
            typename = std::enable_if_t<
                        is_semigroup_v<S> &&
                        detail::are_same_v<S, S1, SS...>>>
  inline constexpr S sconcat(S const& s, S1 const& s1, SS const&... ss)
  {
    return sappend(s, sconcat(s1, ss...));
  }

  template <typename InputIt, typename OutputIt,
            typename S = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_semigroup_v<S>>>
  inline OutputIt spartial_sum(InputIt first, InputIt last, OutputIt out)
  {
    if (first == last)
      return out;
    S val = *first;
    *out++ = val;
    while (++first != last)
    {
      val = sappend(val, *first);
      *out++ = val;
    }
    return out;
  }

  template <typename InputIt1, typename InputIt2, typename OutputIt,
            typename S = typename std::iterator_traits<InputIt1>::value_type,
            typename = std::enable_if_t<is_semigroup_v<S>>>
  inline OutputIt szip(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                       OutputIt out)
  {
    if (first1 == last1)
      return out;
    while (first1 != last1)
      *out++ = sappend(*first1++, *first2++);
    return out;
  }

  template <typename InputIt,
            typename UnaryOp,
            typename S = std::result_of_t<UnaryOp(typename std::iterator_traits<InputIt>::value_type)>,
            typename = std::enable_if_t<is_semigroup_v<S>>>
  inline S stransform_accumulate(InputIt first, InputIt last, UnaryOp op, S init)
  {
    while (first != last)
      init = sappend(init, op(*first++));
    return init;
  }

  template <typename InputIt,
            typename S = typename std::iterator_traits<InputIt>::value_type,
            typename = std::enable_if_t<is_semigroup_v<S>>>
  inline S sintersperse(InputIt first, InputIt last, S e, S init)
  {
    if (first == last)
      return init;
    while (first != last)
      init = sconcat(init, e, *first++);
    return init;
  }
}
