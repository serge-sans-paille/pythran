#ifndef PYTHONIC_BUILTIN_SET_ISSUBSET_HPP
#define PYTHONIC_BUILTIN_SET_ISSUBSET_HPP

#include "pythonic/include/__builtin__/set/issubset.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

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

      DEFINE_FUNCTOR(pythonic::__builtin__::set, issubset);
    }
  }
}
#endif
