#ifndef PYTHONIC_BUILTIN_DICT_POPITEM_HPP
#define PYTHONIC_BUILTIN_DICT_POPITEM_HPP

#include "pythonic/include/__builtin__/dict/popitem.hpp"

#include "pythonic/types/dict.hpp"
#include "pythonic/utils/functor.hpp"

#include <tuple>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace dict
  {

    template <class D>
    auto popitem(D &&d) -> decltype(std::forward<D>(d).popitem())
    {
      return std::forward<D>(d).popitem();
    }
  }
}
PYTHONIC_NS_END

#endif
