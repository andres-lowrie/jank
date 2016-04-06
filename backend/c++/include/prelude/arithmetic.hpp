#pragma once

#include "primitive.hpp"

namespace jank
{
  template <typename A, typename B>
  auto plus(A const &a, B const &b)
  { return a + b; }

  template <typename A, typename B>
  auto minus(A const &a, B const &b)
  { return a - b; }

  auto operator *(string s, integer const n)
  {
    assert_bang(n > 0, "invalid scalar for string repetition");
    auto const original_size(s.size());
    s.reserve(s.size() * n);

    for(integer i{ 1 }; i < n; ++i)
    { s.insert(original_size * i, s.c_str(), original_size); }

    return s;
  }

  template <typename A, typename B>
  auto multiply(A const &a, B const &b)
  { return a * b; }

  template <typename A, typename B>
  auto divide(A const &a, B const &b)
  { return a / b; }
}
