#ifndef PYTHONIC_BUILTIN_FILTER_HPP
#define PYTHONIC_BUILTIN_FILTER_HPP

#include "pythonic/include/__builtin__/filter.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class F, class Iterable>
  types::list<typename Iterable::iterator::value_type>
  filter(F const &f, Iterable const &iterable)
  {
    /* TODO: it does ! implement the full standard (for string && tuple)*/
    types::list<typename Iterable::iterator::value_type> out =
        types::empty_list();
    std::copy_if(iterable.begin(), iterable.end(), std::back_inserter(out), f);
    return out;
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, filter);
}
PYTHONIC_NS_END

#endif
