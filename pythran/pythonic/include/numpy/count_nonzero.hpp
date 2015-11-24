#ifndef PYTHONIC_INCLUDE_NUMPY_COUNT_NONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_COUNT_NONZERO_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class dtype, class E>
    auto _count_nonzero(E begin, E end, size_t &count, utils::int_<1>) ->
        typename std::enable_if<std::is_same<dtype, bool>::value>::type;

    template <class dtype, class E>
    auto _count_nonzero(E begin, E end, size_t &count, utils::int_<1>) ->
        typename std::enable_if<!std::is_same<dtype, bool>::value>::type;

    template <class dtype, class E, size_t N>
    void _count_nonzero(E begin, E end, size_t &count, utils::int_<N>);

    template <class E>
    size_t count_nonzero(E const &array);

    DECLARE_FUNCTOR(pythonic::numpy, count_nonzero);
  }
}

#endif
