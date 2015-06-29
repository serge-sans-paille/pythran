#ifndef PYTHONIC_BUILTIN_LIST_APPEND_HPP
#define PYTHONIC_BUILTIN_LIST_APPEND_HPP

#include "pythonic/include/builtins/list/append.hpp"

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
      types::none_type append(types::list<T> &seq, F &&value)
      {
        seq.push_back(std::forward<F>(value));
        return builtins::None;
      }

      template <class F>
      types::none_type append(types::empty_list &seq, F &&value)
      {
        static_assert(F::this_should_never_happen, "Type inference is wrong.");
        return builtins::None;
      }

      PROXY_IMPL(pythonic::builtins::list, append);
    }
  }
}
#endif
