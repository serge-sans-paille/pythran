#ifndef PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP
#define PYTHONIC_BUILTIN_DICT_ITERITEMS_HPP

#include "pythonic/include/__builtin__/dict/iteritems.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class D>
    auto iteritems(D &&d) -> decltype(std::forward<D>(d).iteritems())
    {
      return std::forward<D>(d).iteritems();
    }
  }
}
PYTHONIC_NS_END

#endif
