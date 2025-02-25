#include <iostream>
#include <sstream>

#include <jank/runtime/seq.hpp>
#include <jank/runtime/util.hpp>
#include <jank/runtime/hash.hpp>
#include <jank/runtime/obj/function.hpp>
#include <jank/runtime/obj/list.hpp>

namespace jank::runtime::obj
{
  list_ptr list::create(runtime::detail::list_type const &l)
  { return make_box<list>(l); }

  runtime::detail::boolean_type list::equal(object const &o) const
  {
    auto const *s(o.as_seqable());
    if(!s)
    { return false; }

    /* TODO: Optimize using better interfaces. */
    auto seq(s->seq());
    for(auto it(data.begin()); it != data.end(); ++it, seq = seq->next())
    {
      if(seq == nullptr || !(*it)->equal(*seq->first()))
      { return false; }
    }
    return true;
  }
  runtime::detail::string_type list::to_string() const
  {
    auto const end(data.end());
    std::stringstream ss;
    ss << "list(";
    for(auto i(data.begin()); i != end; ++i)
    {
      ss << **i;
      auto n(i);
      if(++n != end)
      { ss << " "; }
    }
    ss << ")";
    return ss.str();
  }
  /* TODO: Cache this. */
  runtime::detail::integer_type list::to_hash() const
  {
    size_t seed{ data.size() };
    for(auto const &e : data)
    { seed = runtime::detail::hash_combine(seed, *e); }
    return seed;
  }
  list const* list::as_list() const
  { return this; }
  behavior::seqable const* list::as_seqable() const
  { return this; }
  behavior::sequence_pointer list::seq() const
  {
    if(data.size() == 0)
    { return nullptr; }
    return make_box<behavior::basic_iterator_wrapper<runtime::detail::list_type::iterator>>(data.begin(), data.end());
  }
  size_t list::count() const
  { return data.size(); }
}
