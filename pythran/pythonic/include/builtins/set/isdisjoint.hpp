#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISDISJOINT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISDISJOINT_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {
      template <class T, class U>
      bool isdisjoint(types::set<T> const &calling_set, U const &arg_set);

      template <class U>
      bool isdisjoint(types::empty_set const &calling_set, U const &arg_set);

      PROXY_DECL(pythonic::builtins::set, isdisjoint);
    }
  }
}
#endif
