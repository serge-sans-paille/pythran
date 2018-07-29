#ifndef PYTHONIC_INCLUDE_BUILTIN_FLOAT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FLOAT_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {
    struct float_ {
      using callable = void;
      using type = double;

      template <class T>
      type operator()(T &&t) const;

      type operator()() const;
    };
  }
}
PYTHONIC_NS_END

#endif
