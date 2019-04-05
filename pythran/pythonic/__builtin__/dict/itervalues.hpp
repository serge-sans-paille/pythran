#ifndef PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP
#define PYTHONIC_BUILTIN_DICT_ITERVALUES_HPP

#include "pythonic/include/__builtin__/dict/itervalues.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class D>
    auto itervalues(D &&d) -> decltype(std::forward<D>(d).itervalues())
    {
      return std::forward<D>(d).itervalues();
    }
  }
}
PYTHONIC_NS_END

#endif
