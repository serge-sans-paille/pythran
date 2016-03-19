#ifndef PYTHONIC_BUILTIN_LIST_REVERSE_HPP
#define PYTHONIC_BUILTIN_LIST_REVERSE_HPP

#include "pythonic/include/__builtin__/list/reverse.hpp"

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

      template <class T>
      types::none_type reverse(types::list<T> &seq)
      {
        std::reverse(seq.begin(), seq.end());
        return __builtin__::None;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::list, reverse);
    }
  }
}
#endif
