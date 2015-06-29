#ifndef PYTHONIC_INCLUDE_BUILTIN_FILTER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILTER_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    template <class F, class Iterable>
    types::list<typename Iterable::iterator::value_type>
    filter(F const &f, Iterable const &iterable);

    PROXY_DECL(pythonic::builtins, filter);
  }
}

#endif
