#ifndef PYTHONIC_INCLUDE_NUMPY_STACK_HPP
#define PYTHONIC_INCLUDE_NUMPY_STACK_HPP

#include <pythonic/include/numpy/concatenate.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
    template <class E>
    types::ndarray<typename E::dtype, types::array<long, E::value+1>>
    stack(types::list<E> const &args, long axis = 0);

  DEFINE_FUNCTOR(pythonic::numpy, stack);
}
PYTHONIC_NS_END

#endif
