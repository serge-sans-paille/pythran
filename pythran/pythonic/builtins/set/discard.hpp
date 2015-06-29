#ifndef PYTHONIC_BUILTIN_SET_DISCARD_HPP
#define PYTHONIC_BUILTIN_SET_DISCARD_HPP

#include "pythonic/include/builtins/set/discard.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {
      template <class T, class U>
      void discard(types::set<T> &set, U const &elem)
      {
        set.discard(elem);
      }

      template <class T, class U>
      void discard(types::set<T> &&set, U const &elem)
      {
        // nothing to be done for lvalue
      }

      template <class U>
      void discard(types::empty_set const &set, U const &elem)
      {
        // nothing to remove in an empty_set
      }

      PROXY_IMPL(pythonic::builtins::set, discard);
    }
  }
}
#endif
