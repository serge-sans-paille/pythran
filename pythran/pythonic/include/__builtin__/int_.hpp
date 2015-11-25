#ifndef PYTHONIC_INCLUDE_BUILTIN_INT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_INT_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace functor
    {

      struct int_ {
        using callable = void;
        using type = long;

        template <class T>
        type operator()(T &&t);
        type operator()(char t);
        type operator()();
      };
    }
  }
}

#endif
