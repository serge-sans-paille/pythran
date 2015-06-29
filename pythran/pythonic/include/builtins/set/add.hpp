#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ADD_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/set.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <class T, class F>
      void add(types::set<T> &s, F const &value);

      template <class T, class F>
      void add(types::set<T> &&s, F const &value);

      PROXY_DECL(pythonic::builtins::set, add);
    }
  }
}
#endif
