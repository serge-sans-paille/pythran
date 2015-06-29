#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace pythran
    {

      template <class Iterable>
      long len_set(Iterable const &s);

      PROXY_DECL(pythonic::builtins::pythran, len_set);
    }
  }
}

#endif
