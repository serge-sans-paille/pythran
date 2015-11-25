#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class U>
      bool issuperset(types::set<T> const &set, U const &other);

      template <class U>
      bool issuperset(types::empty_set const &set, U const &other);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, issuperset);
    }
  }
}
#endif
