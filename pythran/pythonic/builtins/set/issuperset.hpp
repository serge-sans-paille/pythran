#ifndef PYTHONIC_BUILTIN_SET_ISSUPERSET_HPP
#define PYTHONIC_BUILTIN_SET_ISSUPERSET_HPP

#include "pythonic/include/builtins/set/issuperset.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <class T, class U>
      bool issuperset(types::set<T> const &set, U const &other)
      {
        return set.issuperset(other);
      }

      template <class U>
      bool issuperset(types::empty_set const &set, U const &other)
      {
        return false;
      }

      PROXY_IMPL(pythonic::builtins::set, issuperset);
    }
  }
}
#endif
