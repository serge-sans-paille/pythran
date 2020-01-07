#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_KWONLY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_KWONLY_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  struct kwonly {
  };
}

namespace builtins
{
  namespace pythran
  {
    types::kwonly kwonly()
    {
      return {};
    };

    DEFINE_FUNCTOR(pythonic::builtins::pythran, kwonly);
  }
}
PYTHONIC_NS_END

#endif
