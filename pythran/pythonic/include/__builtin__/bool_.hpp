#ifndef PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {

    struct bool_ {
      using callable = void;
      using type = bool;

      bool operator()() const;

      template <class T>
      bool operator()(T &&val) const;
    };
  }
}
PYTHONIC_NS_END

#endif
