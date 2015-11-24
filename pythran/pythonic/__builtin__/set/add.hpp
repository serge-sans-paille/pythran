#ifndef PYTHONIC_BUILTIN_SET_ADD_HPP
#define PYTHONIC_BUILTIN_SET_ADD_HPP

#include "pythonic/include/__builtin__/set/add.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class F>
      void add(types::set<T> &s, F const &value)
      {
        s.add(value);
      }

      template <class T, class F>
      void add(types::set<T> &&s, F const &value)
      {
        // nothing have to be done as we work on rvalue
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::set, add);
    }
  }
}
#endif
