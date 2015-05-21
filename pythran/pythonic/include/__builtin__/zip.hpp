#ifndef PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP

#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class List0, class... Lists>
    auto zip(List0 &&s0, Lists &&... lists)
        -> types::list<decltype(types::make_tuple(*s0.begin(),
                                                  *lists.begin()...))>;

    types::empty_list zip();

    PROXY_DECL(pythonic::__builtin__, zip);
  }
}

#endif
