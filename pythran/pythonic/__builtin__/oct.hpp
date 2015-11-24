#ifndef PYTHONIC_BUILTIN_OCT_HPP
#define PYTHONIC_BUILTIN_OCT_HPP

#include "pythonic/include/__builtin__/oct.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <sstream>

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    types::str oct(T const &v)
    {
      std::ostringstream oss;
      oss << '0' << std::oct << v;
      return oss.str();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, oct);
  }
}

#endif
