#ifndef PYTHONIC_BUILTIN_LIST_INDEX_HPP
#define PYTHONIC_BUILTIN_LIST_INDEX_HPP

#include "pythonic/include/__builtin__/list/index.hpp"

#include "pythonic/__builtin__/str.hpp"
#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace list
    {
      template <class T>
      long index(types::list<T> &seq, T const &x)
      {
        long index_value = seq.index(x);
        if (index_value == seq.size())
          throw types::ValueError(__builtin__::anonymous::str(x) +
                                  " is not in list");
        return index_value;
      }

      template <class T>
      long index(types::list<T> &&seq, T const &x)
      {
        long index_value = seq.index(x);
        if (index_value == seq.size())
          throw types::ValueError(__builtin__::anonymous::str(x) +
                                  " is not in list");
        return index_value;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::list, index);
    }
  }
}
#endif
