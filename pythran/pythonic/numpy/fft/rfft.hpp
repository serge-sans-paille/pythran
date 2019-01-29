#ifndef PYTHONIC_NUMPY_FFT_RFFT_HPP
#define PYTHONIC_NUMPY_FFT_RFFT_HPP

#include "pythonic/include/numpy/fft/rfft.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/swapaxes.hpp"

#include <mutex>
#include <map>

#include "pythonic/numpy/fft/fftpack.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {
    std::mutex mtx_rfft; // mutex for critical section

    // Aux function
    template <class T, class pS>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    _rfft(types::ndarray<T, pS> const &in_array, long NFFT, bool norm)
    {
      long i;
      auto &&shape = in_array.shape();
      T *dptr = (T *)in_array.buffer;
      long npts = std::get<std::tuple_size<pS>::value - 1>(shape);

      // Create output array.
      long out_size = NFFT / 2 + 1;
      auto out_shape = sutils::array(shape);
      out_shape.back() = out_size;
      types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                     types::array<long, std::tuple_size<pS>::value>>
          out_array(out_shape, __builtin__::None);

      // Create the twiddle factors. These must be kept from call to call as
      // it's very wasteful to recompute them.
      // The call to npy_rfftf makes changes to the twiddle factor buffer (then
      // restores it) so it's
      // not thread safe. To avoid this:
      // I keep one copy of the twiddle factors that no thread is allowed to
      // modify. Then each thread
      // has its own copy of it that it can modify at will.
      // This is from fftpack_litemodule.c
      static std::map<long, std::vector<double>> all_twiddles_rfft_global;
      static thread_local std::map<long, std::vector<double>>
          all_twiddles_rfft_local;
      mtx_rfft.lock();
      if (all_twiddles_rfft_global.find(NFFT) ==
          all_twiddles_rfft_global.end()) {
        // This happens only once across all threads for a give NFFT
        // Insert a new twiddle array into our map and initialize it
        all_twiddles_rfft_global.emplace(NFFT,
                                         std::vector<double>(2 * NFFT + 15));
        // This is the (costly) initialization of the array.
        npy_rffti(NFFT, all_twiddles_rfft_global[NFFT].data());
      }

      if (all_twiddles_rfft_local.find(NFFT) == all_twiddles_rfft_local.end()) {
        // This happens once per thread.
        all_twiddles_rfft_local.emplace(NFFT, all_twiddles_rfft_global[NFFT]);
      }

      double *twiddle_buffer = all_twiddles_rfft_local[NFFT].data();
      mtx_rfft.unlock();

      // Call fft (fftpack.py) r = work_function(in_array, wsave)
      // This is translated from
      // https://raw.githubusercontent.com/numpy/numpy/master/numpy/fft/fftpack_litemodule.c

      double *rptr = (double *)out_array.buffer;
      long nrepeats = in_array.flat_size() / npts;
      long to_copy = (NFFT <= npts) ? NFFT : npts;
      for (i = 0; i < nrepeats; i++) {
        rptr[2 * out_size - 1] = 0.0; // We didn't zero the array upon
                                      // allocation. Make sure the last element
                                      // is 0.
        std::copy(dptr, dptr + to_copy, rptr + 1);
        // Zero padding if the FFT size is > the number points
        std::fill(rptr + 1 + to_copy, rptr + 1 + to_copy + (NFFT - to_copy), 0);
        npy_rfftf(NFFT, rptr + 1, twiddle_buffer);
        rptr[0] = rptr[1];
        rptr[1] = 0.0;
        rptr += 2 * out_size;
        dptr += npts;
      }
      if (norm) {
        double scale = 1. / sqrt(NFFT);
        rptr = (double *)out_array.buffer;
        long count = 2 * out_array.flat_size();
        // Remember that these are complex numbers!
        for (i = 0; i < count; i++) {
          rptr[i] *= scale;
        }
      }
      return out_array;
    }

    template <class T, class pS>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    rfft(types::ndarray<T, pS> const &in_array, long NFFT, long axis)
    {
      return rfft(in_array, NFFT, axis, "");
    }

    // This is kludgy, and I'm sure there's a better way to do this. Jeanl
    bool testThis(types::none_type param)
    {
      return false;
    }
    bool testThis(types::str param)
    {
      return param == "ortho";
    }

    template <class T, class pS, typename U>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    rfft(types::ndarray<T, pS> const &in_array, long NFFT, long axis,
         U normalize)
    {
      bool norm = testThis(normalize);
      auto constexpr N = std::tuple_size<pS>::value;

      if (NFFT == -1)
        NFFT = std::get<N - 1>(in_array.shape());
      if (axis != -1 && axis != N - 1) {
        // Swap axis if the FFT must be computed on an axis that's not the last
        // one.
        auto swapped_array = swapaxes(in_array, axis, N - 1);
        return swapaxes(_rfft(swapped_array, NFFT, norm), axis, N - 1);
      } else {
        return _rfft(in_array, NFFT, norm);
      }
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(rfft);
  }
}
PYTHONIC_NS_END

#endif
