#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_INSERT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_INSERT_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/none.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace list
    {

      template <class T, class F>
      types::none_type insert(types::list<T> &seq, long n, F &&value);

      PROXY_DECL(pythonic::builtins::list, insert);
    }
  }
}
#endif
