#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_EXTEND_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_EXTEND_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/none.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace list
    {

      template <class T, class F>
      types::none_type extend(types::list<T> &seq, types::list<F> const &add);

      DECLARE_FUNCTOR(pythonic::__builtin__::list, extend);
    }
  }
}
#endif
