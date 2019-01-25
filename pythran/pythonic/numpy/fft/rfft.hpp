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
      // This is from fftpack_litemodule.c
      mtx_rfft.lock();
      static std::map<long, types::ndarray<double, types::pshape<long>>>
          all_twiddles_rfft;
      if (all_twiddles_rfft.find(NFFT) == all_twiddles_rfft.end()) {
        // Insert a new twiddle array into our map and initialize it
        all_twiddles_rfft.insert(std::make_pair(
            NFFT, types::ndarray<double, types::pshape<long>>(
                      {(long)(2 * NFFT + 15)}, __builtin__::None)));
        npy_rffti(NFFT, (double *)all_twiddles_rfft[NFFT].buffer);
      }
      mtx_rfft.unlock();

      // Call fft (fftpack.py) r = work_function(in_array, wsave)
      // This is translated from
      // https://raw.githubusercontent.com/numpy/numpy/master/numpy/fft/fftpack_litemodule.c

      double *rptr = (double *)out_array.buffer;
      double *twiddle_buffer = (double *)all_twiddles_rfft[NFFT].buffer;
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

    // These functions help handle None inputs for default values without
    // relying on the C++ default mechanism.
    bool testNorm(types::none_type param)
    {
      return false;
    }
    bool testNorm(types::str param)
    {
      if (param == "ortho")
        return 1;
      else {
        throw types::ValueError("norm should be None or \"ortho\"");
        return 0;
      }
    }

    long testLong(types::none_type param, long def_val)
    {
      return def_val;
    }
    long testLong(long N, long def_val)
    {
      return N;
    }

    template <class T, class pS, typename U, typename V, typename W>
    types::ndarray<std::complex<typename std::common_type<T, double>::type>,
                   types::array<long, std::tuple_size<pS>::value>>
    rfft(types::ndarray<T, pS> const &in_array, U _NFFT, V _axis, W normalize)
    {
      bool norm = testNorm(normalize);
      auto constexpr N = std::tuple_size<pS>::value;
      // Handle None for axis input.
      long axis = testLong(_axis, -1);
      // Handle None for NFFT. Map -1 -> N-1 etc...
      long LN = (long)N;
      if (axis >= LN)
        throw types::ValueError("axis out of bounds1");
      if (axis <= -LN - 1)
        throw types::ValueError("axis out of bounds");
      axis = (axis + LN) % LN;
      long def_val = sutils::array(in_array.shape())[axis];
      long NFFT = testLong(_NFFT, def_val);
      if (axis != LN - 1) {
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
