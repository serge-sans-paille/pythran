#ifndef PYTHONIC_BUILTIN_SET_ADD_HPP
#define PYTHONIC_BUILTIN_SET_ADD_HPP

#include "pythonic/include/__builtin__/set/add.hpp"

#include "pythonic/__builtin__/None.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/set.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class F>
      types::none_type add(types::set<T> &s, F const &value)
      {
        s.add(value);
        return __builtin__::None;
      }

      template <class T, class F>
      types::none_type add(types::set<T> &&s, F const &value)
      {
        s.add(value);
        return __builtin__::None;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::set, add);
    }
  }
}
#endif
