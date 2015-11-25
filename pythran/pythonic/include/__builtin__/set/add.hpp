#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/set.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class F>
      void add(types::set<T> &s, F const &value);

      template <class T, class F>
      void add(types::set<T> &&s, F const &value);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, add);
    }
  }
}
#endif
