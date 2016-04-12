#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class F>
      types::none_type add(types::set<T> &s, F const &value);

      template <class T, class F>
      types::none_type add(types::set<T> &&s, F const &value);

      template <class F>
      types::none_type add(types::empty_set const &s, F &&value);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, add);
    }
  }
}
#endif
