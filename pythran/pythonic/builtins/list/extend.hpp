#ifndef PYTHONIC_BUILTIN_LIST_EXTEND_HPP
#define PYTHONIC_BUILTIN_LIST_EXTEND_HPP

#include "pythonic/include/builtins/list/extend.hpp"

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

      template <class T, class F>
      types::none_type extend(types::list<T> &seq, types::list<F> const &add)
      {
        seq += add;
        return builtins::None;
      }

      PROXY_IMPL(pythonic::builtins::list, extend);
    }
  }
}
#endif
