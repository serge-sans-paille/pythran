#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/dict.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class D>
    auto iteritems(D &&d) -> decltype(std::forward<D>(d).iteritems());

    DEFINE_FUNCTOR(pythonic::__builtin__::dict, iteritems);
  }
}
PYTHONIC_NS_END

#endif
