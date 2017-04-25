#ifndef PYTHONIC_INCLUDE_NUMPY_FREXP_HPP
#define PYTHONIC_INCLUDE_NUMPY_FREXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    typename std::enable_if<std::is_scalar<T>::value, std::tuple<T, int>>::type
    frexp(T val);

    template <class E>
    typename std::enable_if<
        not types::is_dtype<E>::value,
        std::tuple<types::ndarray<typename E::dtype, E::value>,
                   types::ndarray<int, E::value>>>::type
    frexp(E const &arr);

    DECLARE_FUNCTOR(pythonic::numpy, frexp);
  }
}

#endif
