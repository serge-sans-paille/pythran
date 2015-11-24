#ifndef PYTHONIC_DISPATCH_CONJUGATE_HPP
#define PYTHONIC_DISPATCH_CONJUGATE_HPP

#include "pythonic/include/__dispatch__/conjugate.hpp"

#include "pythonic/numpy/conjugate.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __dispatch__
  {
    template <class Any>
    auto conjugate(Any const &any) -> decltype(numpy::functor::conjugate{}(any))
    {
      return numpy::functor::conjugate{}(any);
    }

    DEFINE_FUNCTOR(pythonic::__dispatch__, conjugate);
  }
}

#endif
