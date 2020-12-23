#ifndef PYTHONIC_INCLUDE_NUMPY_FFT_FFT_HPP
#define PYTHONIC_INCLUDE_NUMPY_FFT_FFT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {

    template <class T, class pS>
    types::ndarray<std::complex<T>,
            types::array<long, std::tuple_size<pS>::value>>
    fft(types::ndarray<std::complex<T>, pS> const &, long NFFT = -1, long axis = -1,
          types::str const &norm = "");

    NUMPY_EXPR_TO_NDARRAY0_DECL(fft);
    DEFINE_FUNCTOR(pythonic::numpy::fft, fft);
  }
}
PYTHONIC_NS_END


#endif
