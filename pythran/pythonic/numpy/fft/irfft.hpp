#ifndef PYTHONIC_NUMPY_FFT_IRFFT_HPP
#define PYTHONIC_NUMPY_FFT_IRFFT_HPP

#include "pythonic/include/numpy/fft/irfft.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/swapaxes.hpp"

#include <array>
#include <map>
#include <cstring>
#include <cmath>
#include <mutex>
#include <cstdio>

#include "pythonic/numpy/fft/fftpack.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {
    std::mutex mtx_irfft; // mutex for critical section

    // Aux function
    template <class T, class pS>
    types::ndarray<double, types::array<long, std::tuple_size<pS>::value>>
    _irfft(types::ndarray<T, pS> const &in_array, long NFFT, bool norm)
    {
      long i;
      auto const &shape = in_array.shape();
      long npts = std::get<std::tuple_size<pS>::value - 1>(shape);
      // Create output array.
      long out_size = NFFT;
      auto out_shape = sutils::array(shape);
      out_shape.back() = out_size;
      types::ndarray<double, types::array<long, std::tuple_size<pS>::value>>
          out_array(out_shape, __builtin__::None);

      // Create the twiddle factors. These must be kept from call to call as
      // it's very wasteful to recompute them.
      // The call to npy_irfftf makes changes to the twiddle factor buffer (then
      // restores it) so it's
      // not thread safe. To avoid this:
      // I keep one copy of the twiddle factors that no thread is allowed to
      // modify. Then each thread
      // has its own copy of it that it can modify at will.
      // This is from fftpack_litemodule.c
      static std::map<long, std::vector<double>> all_twiddles_irfft_global;
      static thread_local std::map<long, std::vector<double>>
          all_twiddles_irfft_local;
      mtx_irfft.lock();
      if (all_twiddles_irfft_global.find(NFFT) ==
          all_twiddles_irfft_global.end()) {
        // This happens only once across all threads for a give NFFT
        // Insert a new twiddle array into our map and initialize it
        all_twiddles_irfft_global.emplace(NFFT,
                                          std::vector<double>(2 * NFFT + 15));
        // std::cout << "INIT GLOBAL " << NFFT << " \n";
        // This is the (costly) initialization of the array.
        npy_rffti(NFFT, all_twiddles_irfft_global[NFFT].data());
      }

      if (all_twiddles_irfft_local.find(NFFT) ==
          all_twiddles_irfft_local.end()) {
        // This happens once per thread.
        all_twiddles_irfft_local.emplace(NFFT, all_twiddles_irfft_global[NFFT]);
      }

      double *twiddle_buffer = all_twiddles_irfft_local[NFFT].data();
      mtx_irfft.unlock();

      // Call fft (fftpack.py) r = work_function(in_array, wsave)
      // This is translated from
      // https://raw.githubusercontent.com/numpy/numpy/master/numpy/fft/fftpack_litemodule.c

      double *rptr = (double *)out_array.buffer;
      typename T::value_type *dptr = (typename T::value_type *)in_array.buffer;
      long nrepeats = out_array.flat_size() / out_size;
      long to_copy = (NFFT / 2 + 1 <= npts) ? (NFFT - 1) : (2 * npts - 2);
      for (i = 0; i < nrepeats; i++) {
        // By default npts = floor(NFFT/2)+1.
        std::copy(dptr + 2, dptr + 2 + to_copy, rptr + 1);
        rptr[0] = dptr[0];
        // Zero padding if necessary
        std::fill(rptr + 1 + to_copy, rptr + 1 + to_copy + (NFFT - 1 - to_copy),
                  0);
        npy_rfftb(NFFT, rptr, twiddle_buffer);
        rptr += out_size;
        dptr += 2 * npts; // These are comlex numbers.
      }

      double scale = (norm) ? 1. / sqrt(NFFT) : 1. / NFFT;
      rptr = (double *)out_array.buffer;
      long count = out_array.flat_size();
      for (i = 0; i < count; i++) {
        rptr[i] *= scale;
      }
      return out_array;
    }

    template <class T, class pS>
    types::ndarray<double, types::array<long, std::tuple_size<pS>::value>>
    irfft(types::ndarray<T, pS> const &in_array, long NFFT, long axis,
          types::str normalize)
    {
      auto constexpr N = std::tuple_size<pS>::value;
      bool norm = (normalize == "ortho");
      if (NFFT == -1)
        NFFT = 2 * (std::get<N - 1>(in_array.shape()) - 1);
      if (axis != -1 && axis != N - 1) {
        // Swap axis if the FFT must be computed on an axis that's not the last
        // one.
        auto swapped_array = swapaxes(in_array, axis, N - 1);
        return swapaxes(_irfft(swapped_array, NFFT, norm), axis, N - 1);
      } else {
        return _irfft(in_array, NFFT, norm);
      }
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(irfft);
  }
}
PYTHONIC_NS_END

#endif
