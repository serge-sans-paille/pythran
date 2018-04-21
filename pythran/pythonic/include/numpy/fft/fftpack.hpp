#ifndef PYTHONIC_INCLUDE_NUMPY_FFT_FFTPACK_HPP
#define PYTHONIC_INCLUDE_NUMPY_FFT_FFTPACK_HPP
/*
 * This file is part of tela the Tensor Language.
 * Copyright (c) 1994-1995 Pekka Janhunen
 */

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace fft
  {

    void npy_cfftf(int N, double data[], const double wrk[]);
    void npy_cfftb(int N, double data[], const double wrk[]);
    void npy_cffti(int N, double wrk[]);

    void npy_rfftf(int N, double data[], const double wrk[]);
    void npy_rfftb(int N, double data[], const double wrk[]);
    void npy_rffti(int N, double wrk[]);
  }
}
PYTHONIC_NS_END

#endif
