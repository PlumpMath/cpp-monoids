/*
  cpp-monoids - Monoids for C++
  Copyright © 2016 Rüdiger Hanke
  Licensed under BSD3 license - see LICENSE file for details
 */

#pragma once

#include <map>

namespace algebra
{
  template <typename K, typename V, typename Compare, typename Allocator>
  struct is_semigroup<std::map<K, V, Compare, Allocator>> : is_semigroup_t<V> {};
  template <typename K, typename V, typename Compare, typename Allocator>
  struct is_monoid<std::map<K, V, Compare, Allocator>> : is_semigroup_t<V> {};

  template <typename K, typename V, typename Compare, typename Allocator>
  struct semigroup<std::map<K, V, Compare, Allocator>>
  {
    using map_type = std::map<K, V, Compare, Allocator>;

    static constexpr map_type append(map_type a, map_type b) {
      map_type res;
      auto a_it = a.cbegin();
      auto b_it = b.cbegin();
      Compare less;
      while (a_it != a.cend() && b_it != b.cend())
      {
        if (less(a_it->first, b_it->first))
        {
          res.insert(*a_it);
          ++a_it;
        }
        else if (less(b_it->first, a_it->first))
        {
          res.insert(*b_it);
          ++b_it;
        }
        else
        {
          res.insert(std::make_pair(a_it->first, sappend(a_it->second, b_it->second)));
          ++a_it;
          ++b_it;
        }
      }
      
      res.insert(a_it, a.cend());
      res.insert(b_it, b.cend());

      return res;
    }
  };

  template <typename K, typename V, typename Compare, typename Allocator>
  struct monoid<std::map<K, V, Compare, Allocator>>
    : semigroup<std::map<K, V, Compare, Allocator>>
  {
    using map_type = std::map<K, V, Compare, Allocator>;

    static constexpr map_type zero() {
      return map_type();
    }
  };
}
