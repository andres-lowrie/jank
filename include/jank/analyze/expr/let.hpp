#pragma once

#include <list>

#include <jank/runtime/obj/symbol.hpp>
#include <jank/analyze/expr/do.hpp>
#include <jank/analyze/frame.hpp>

namespace jank::analyze::expr
{
  template <typename E>
  struct let
  {
    using pair_type = std::pair<runtime::obj::symbol_ptr, E>;
    /* Stable references. */
    std::list<pair_type> pairs;
    do_<E> body;
    frame<E> local_frame;
  };
}
