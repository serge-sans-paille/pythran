#ifndef PYTHONIC_NUMPY_FFT_FFT_HPP
#define PYTHONIC_NUMPY_FFT_FFT_HPP

#include "pythonic/include/numpy/fft/fft.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/builtins/None.hpp"
#include "pythonic/numpy/concatenate.hpp"
#include "pythonic/numpy/zeros.hpp"


#include <array>
#include <cstring>
#include <cmath>

#include "pythonic/numpy/fft/pocketfft.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {
    using pocketfft::stride_t;
    using pocketfft::shape_t;
    using ldbl_t = typename std::conditional<sizeof(long double)==sizeof(double), double, long double>::type;

    template<typename T> T norm_fct(int inorm, size_t N)
    {
        if (inorm==0) return T(1);
        if (inorm==2) return T(1/ldbl_t(N));
        if (inorm==1) return T(1/sqrt(ldbl_t(N)));
            throw std::invalid_argument("invalid value for inorm (must be 0, 1, or 2)");
    }

    template<typename T> T norm_fct(int inorm, const shape_t &shape,
    const shape_t &axes, size_t fct=1, int delta=0)
    {
    if (inorm==0) return T(1);
    size_t N(1);
    for (auto a: axes)
        N *= fct * size_t(int64_t(shape[a])+delta);
    return norm_fct<T>(inorm, N);
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    fft(types::ndarray<std::complex<T>, pS> const &in_array, types::none_type n, long axis,
          types::str const &norm)
    {
        return fft(in_array, -1, axis, norm);
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    fft(types::ndarray<std::complex<T>, pS> const &in_array, types::none_type n, long axis,
          types::none_type norm)
    {
        return fft(in_array, -1, axis, "");
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    fft(types::ndarray<std::complex<T>, pS> const &in_array, long n, long axis,
          types::none_type norm)
    {
        return fft(in_array, n, axis, "");
    }

    template <class T , class pS>
    stride_t create_strides(types::ndarray<T, pS> const &in_array)
    {
        long npts = in_array.template shape<std::tuple_size<pS>::value - 1>();
        auto constexpr N = std::tuple_size<pS>::value;
        auto shape = sutils::getshape(in_array);
        stride_t strides = stride_t(N);
        strides[N-1] = sizeof(T);
        std::transform(strides.rbegin(), strides.rend() - 1, shape.rbegin(),
                  strides.rbegin() + 1, std::multiplies<long>());
        return strides;
    }

    template <class T , class pS>
    types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
    fft(types::ndarray<std::complex<T>, pS> const &in_array, long n, long axis,
          types::str const &norm)
    {
      long i;
      auto constexpr N = std::tuple_size<pS>::value;
      int inorm = (norm == "ortho");
      if (axis < 0)
        axis = N + axis;
      auto in_shape = sutils::getshape(in_array);
      long npts = in_shape[axis];
      if (n == -1)
        n = npts;
      auto out_shape = sutils::getshape(in_array);
      out_shape[axis] = n;
      // Create output array.
      types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>
          out_array(out_shape, builtins::None);
      std::complex<T> *  d_in;
      types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>> extended_array;
      if (n > npts){
        // extend array with zeros along axis direction
        auto tmp_shape = sutils::getshape(out_array);
        tmp_shape[axis] = n - npts;
        auto tmp_array = zeros(tmp_shape, types::dtype_t<typename std::complex<T>>());
        types::list<types::ndarray<std::complex<T>, types::array<long, std::tuple_size<pS>::value>>> bi(0);
        bi.push_back(in_array);
        bi.push_back(tmp_array);
        extended_array = concatenate(bi, axis);
        d_in = reinterpret_cast<std::complex<T> *>(extended_array.buffer);
      } else
        d_in = reinterpret_cast<std::complex<T> *>(in_array.buffer);
      auto d_out = reinterpret_cast<std::complex<T> *>(out_array.buffer);
      // axes calculation is for 1D transform
      shape_t axes = shape_t(1);
      axes[0] = axis;
      stride_t in_strides;
      if (n < npts)
        in_strides = create_strides(in_array); // for cropped arrays we need to use different strides
      else
        in_strides = create_strides(out_array);
      auto out_strides = create_strides(out_array);
      shape_t shapes = shape_t(size_t(N));
      for (std::size_t i=0; i<N; ++i)
        shapes[i] = size_t(out_shape[i]);
      auto fct = norm_fct<T>(inorm, shapes, axes);
      pocketfft::c2c(shapes, in_strides, out_strides, axes, true, d_in, d_out, fct);
      return out_array;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(fft);
  }
}
PYTHONIC_NS_END

#endif
