#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISSUPERSET_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <class T, class U>
      bool issuperset(types::set<T> const &set, U const &other);

      template <class U>
      bool issuperset(types::empty_set const &set, U const &other);

      PROXY_DECL(pythonic::builtins::set, issuperset);
    }
  }
}
#endif
