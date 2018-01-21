#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_LEN_SET_HPP

#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {

    template <class Iterable>
    long len_set(Iterable const &s);

    DECLARE_FUNCTOR(pythonic::__builtin__::pythran, len_set);
  }
}
PYTHONIC_NS_END

#endif
