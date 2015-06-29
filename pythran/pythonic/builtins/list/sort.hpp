#ifndef PYTHONIC_BUILTIN_LIST_SORT_HPP
#define PYTHONIC_BUILTIN_LIST_SORT_HPP

#include "pythonic/include/builtins/list/sort.hpp"

#include "pythonic/builtins/None.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/none.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      template <class T>
      types::none_type sort(types::list<T> &seq)
      {
        std::sort(seq.begin(), seq.end());
        return builtins::None;
      }

      PROXY_IMPL(pythonic::builtins::list, sort);
    }
  }
}
#endif
