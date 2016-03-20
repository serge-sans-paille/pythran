#ifndef PYTHONIC_BUILTIN_LIST_INSERT_HPP
#define PYTHONIC_BUILTIN_LIST_INSERT_HPP

#include "pythonic/include/__builtin__/list/insert.hpp"

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

      // TODO : range_analysis may be use to have a "fast insert" function.
      template <class T, class F>
      types::none_type insert(types::list<T> &seq, long n, F &&value)
      {
        n = n % (1 + seq.size()); // +1 because we want to be able to insert at
                                  // the end of seq
        if (n < 0)
          n += seq.size();
        seq.insert(n, std::forward<F>(value));
        return __builtin__::None;
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::list, insert);
    }
  }
}
#endif
