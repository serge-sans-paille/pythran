#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_APPEND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_APPEND_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace list
    {

      template <class T, class F>
      types::none_type append(types::list<T> &seq, F &&value);

      template <class T, class F>
      types::none_type append(types::list<T> &&seq, F &&value);

      template <class F>
      types::none_type append(types::empty_list &seq, F &&value);

      DECLARE_FUNCTOR(pythonic::__builtin__::list, append);
    }
  }
}
#endif
