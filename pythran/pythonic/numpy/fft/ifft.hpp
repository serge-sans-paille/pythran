#ifndef PYTHONIC_NUMPY_FFT_IFFT_HPP
#define PYTHONIC_NUMPY_FFT_IFFT_HPP

#include "pythonic/include/numpy/fft/ifft.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/builtins/None.hpp"
#include "pythonic/numpy/concatenate.hpp"
#include "pythonic/numpy/zeros.hpp"


#include <array>
#include <cstring>
#include <cmath>

#include "pythonic/numpy/fft/c2c.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {
    using pocketfft::stride_t;
    using pocketfft::shape_t;
    using ldbl_t = typename std::conditional<sizeof(long double)==sizeof(double), double, long double>::type;

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &in_array, types::none_type n, long axis,
          types::str const &norm)
    {
        return c2c(in_array, -1, axis, norm, false);
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &in_array, types::none_type n, long axis,
          types::none_type norm)
    {
        return c2c(in_array, -1, axis, "", false);
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &in_array, long n, long axis,
          types::none_type norm)
    {
        return c2c(in_array, n, axis, "", false);
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &in_array, long n, long axis,
          types::str const &norm)
    {
        return c2c(in_array, n, axis, norm, false);
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(ifft);
  }
}
PYTHONIC_NS_END

#endif
