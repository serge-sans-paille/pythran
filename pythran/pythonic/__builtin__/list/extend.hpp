#ifndef PYTHONIC_BUILTIN_LIST_EXTEND_HPP
#define PYTHONIC_BUILTIN_LIST_EXTEND_HPP

#include "pythonic/include/__builtin__/list/extend.hpp"

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
      types::none_type extend(types::list<T> &seq, types::list<F> const &add)
      {
        seq += add;
        return __builtin__::None;
      }

      template <class T, class F>
      types::none_type extend(types::list<T> &&seq, types::list<F> const &add)
      {
        std::move(seq) += add;
        return __builtin__::None;
      }
      template <class F>
      types::none_type extend(types::empty_list, types::list<F> const &)
      {
        return __builtin__::None;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::list, extend);
    }
  }
}
#endif
