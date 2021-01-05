#ifndef PYTHONIC_INCLUDE_NUMPY_FFT_IFFT_HPP
#define PYTHONIC_INCLUDE_NUMPY_FFT_IFFT_HPP

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
    ifft(types::ndarray<std::complex<T>, pS> const &a, long n = -1, long axis = -1,
          types::str const &norm = {});

    template <class T, class pS>
    types::ndarray<std::complex<T>,
            types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &a, types::none_type n, long axis,
          types::str const &norm );

    template <class T, class pS>
    types::ndarray<std::complex<T>,
            types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &a, long n, long axis,
          types::none_type norm );

    template <class T, class pS>
    types::ndarray<std::complex<T>,
            types::array<long, std::tuple_size<pS>::value>>
    ifft(types::ndarray<std::complex<T>, pS> const &a, types::none_type n , long axis =-1,
          types::none_type norm = types::none_type{});

    NUMPY_EXPR_TO_NDARRAY0_DECL(ifft);
    DEFINE_FUNCTOR(pythonic::numpy::fft, ifft);
  }
}
PYTHONIC_NS_END


#endif
