#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_DISCARD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_DISCARD_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {
      template <class T, class U>
      void discard(types::set<T> &set, U const &elem);

      template <class T, class U>
      void discard(types::set<T> &&set, U const &elem);

      template <class U>
      void discard(types::empty_set const &set, U const &elem);

      PROXY_DECL(pythonic::builtins::set, discard);
    }
  }
}
#endif
