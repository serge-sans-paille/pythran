#ifndef PYTHONIC_BUILTIN_SET_ISSUBSET_HPP
#define PYTHONIC_BUILTIN_SET_ISSUBSET_HPP

#include "pythonic/include/__builtin__/set/issubset.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace set
  {

    template <class T, class U>
    bool issubset(types::set<T> const &set, U const &other)
    {
      return set.issubset(other);
    }

    template <class U>
    bool issubset(types::empty_set const &set, U const &other)
    {
      return true;
    }
  }
}
PYTHONIC_NS_END
#endif
