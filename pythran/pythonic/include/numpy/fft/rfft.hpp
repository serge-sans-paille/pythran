#ifndef PYTHONIC_INCLUDE_NUMPY_FFT_RFFT_HPP
#define PYTHONIC_INCLUDE_NUMPY_FFT_RFFT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {

    // I'm sure there's a better way to do this.
    template <class T, class pS, typename U>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    rfft(types::ndarray<T, pS> const &input, long NFFT = -1, long axis = -1,
         U renorm = types::str(""));

    template <class T, class pS>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    rfft(types::ndarray<T, pS> const &input, long NFFT = -1, long axis = -1);

    NUMPY_EXPR_TO_NDARRAY0_DECL(rfft);
    DEFINE_FUNCTOR(pythonic::numpy::fft, rfft);
  }
}
PYTHONIC_NS_END

#endif
