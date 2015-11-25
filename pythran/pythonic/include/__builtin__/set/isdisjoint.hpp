#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISDISJOINT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISDISJOINT_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {
      template <class T, class U>
      bool isdisjoint(types::set<T> const &calling_set, U const &arg_set);

      template <class U>
      bool isdisjoint(types::empty_set const &calling_set, U const &arg_set);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, isdisjoint);
    }
  }
}
#endif
