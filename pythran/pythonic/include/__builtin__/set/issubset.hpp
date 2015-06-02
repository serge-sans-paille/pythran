#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_ISSUBSET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_ISSUBSET_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <class T, class U>
      bool issubset(types::set<T> const &set, U const &other);

      template <class U>
      bool issubset(types::empty_set const &set, U const &other);

      PROXY_DECL(pythonic::__builtin__::set, issubset);
    }
  }
}
#endif
