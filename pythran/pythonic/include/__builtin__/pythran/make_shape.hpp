#ifndef PYTHONIC_INCLUDE_BUILTIN_MAKE_SHAPE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MAKE_SHAPE_HPP

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  namespace pythran
  {
    template <class... Args>
    pythonic::types::pshape<Args...> make_shape(Args... args);

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, make_shape);
  } // pythran
} // __builtin__
PYTHONIC_NS_END

#endif
