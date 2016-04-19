#ifndef PYTHONIC_BUILTIN_LIST_APPEND_HPP
#define PYTHONIC_BUILTIN_LIST_APPEND_HPP

#include "pythonic/include/__builtin__/list/append.hpp"

#include "pythonic/__builtin__/None.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace list
    {

      template <class T, class F>
      types::none_type append(types::list<T> &seq, F &&value)
      {
        seq.push_back(std::forward<F>(value));
        return __builtin__::None;
      }
      template <class T, class F>
      types::none_type append(types::list<T> &&seq, F &&value)
      {
        seq.push_back(std::forward<F>(value));
        return __builtin__::None;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::list, append);
    }
  }
}
#endif
