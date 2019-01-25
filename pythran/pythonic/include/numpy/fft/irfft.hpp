#ifndef PYTHONIC_INCLUDE_NUMPY_FFT_IRFFT_HPP
#define PYTHONIC_INCLUDE_NUMPY_FFT_IRFFT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {

    template <class T, class pS, typename U, typename V, typename W>
    types::ndarray<double, types::array<long, std::tuple_size<pS>::value>>
    irfft(types::ndarray<T, pS> const &, U NFFT, V axis, W renorm);

    NUMPY_EXPR_TO_NDARRAY0_DECL(irfft);
    DEFINE_FUNCTOR(pythonic::numpy::fft, irfft);
  }
}
PYTHONIC_NS_END

#endif
