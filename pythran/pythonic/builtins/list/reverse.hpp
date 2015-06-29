#ifndef PYTHONIC_BUILTIN_LIST_REVERSE_HPP
#define PYTHONIC_BUILTIN_LIST_REVERSE_HPP

#include "pythonic/include/builtins/list/reverse.hpp"

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
      types::none_type reverse(types::list<T> &seq)
      {
        std::reverse(seq.begin(), seq.end());
        return builtins::None;
      }

      PROXY_IMPL(pythonic::builtins::list, reverse);
    }
  }
}
#endif
