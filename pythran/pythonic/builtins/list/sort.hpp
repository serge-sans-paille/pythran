#ifndef PYTHONIC_BUILTIN_LIST_SORT_HPP
#define PYTHONIC_BUILTIN_LIST_SORT_HPP

#include "pythonic/include/builtins/list/sort.hpp"

#include "pythonic/builtins/None.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

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
  }
}
PYTHONIC_NS_END
#endif
