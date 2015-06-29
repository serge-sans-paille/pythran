#ifndef PYTHONIC_BUILTIN_LIST_INDEX_HPP
#define PYTHONIC_BUILTIN_LIST_INDEX_HPP

#include "pythonic/include/builtins/list/index.hpp"

#include "pythonic/builtins/str.hpp"
#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {
      template <class T>
      long index(types::list<T> &seq, T const &x)
      {
        long index_value = seq.index(x);
        if (index_value == seq.size())
          throw types::ValueError(builtins::anonymous::str(x) +
                                  " is not in list");
        return index_value;
      }

      template <class T>
      long index(types::list<T> &&seq, T const &x)
      {
        long index_value = seq.index(x);
        if (index_value == seq.size())
          throw types::ValueError(builtins::anonymous::str(x) +
                                  " is not in list");
        return index_value;
      }

      PROXY_IMPL(pythonic::builtins::list, index);
    }
  }
}
#endif
