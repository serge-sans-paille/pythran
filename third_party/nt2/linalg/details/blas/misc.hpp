//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_MISC_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_MISC_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_MISC(T, PREFIX, NAME)                               \
inline void NAME( const long int *n                             \
                , T *x, const long int *incx                    \
                , T *y, const long int *incy                    \
                )                                               \
{                                                               \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,NAME))(n, x, incx, y, incy);  \
}                                                               \
/**/

  // INTERNAL ONLY
  // swap
  // SUBROUTINE _SWAP ( N, X, INCX, Y, INCY ) S, D, C, Z
  NT2_MISC(double, d, swap)
  NT2_MISC(float,  s, swap)
  NT2_MISC(std::complex<double>, z, swap)
  NT2_MISC(std::complex<float>,  c, swap)
#undef NT2_MISC

#define NT2_MISC(T, PREFIX, NAME)                               \
inline void NAME( const long int *n                             \
                , const T *x, const long int *incx              \
                , T *y      , const long int *incy              \
                )                                               \
{                                                               \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,NAME))(n, x, incx, y, incy);  \
}                                                               \
/**/

  // INTERNAL ONLY
  // copy
  // SUBROUTINE _COPY ( N, X, INCX, Y, INCY ) S, D, C, Z
  NT2_MISC(double, d, copy)
  NT2_MISC(float,  s, copy)
  NT2_MISC(std::complex<double>, z, copy)
  NT2_MISC(std::complex<float>,  c, copy)

#define NT2_MISC(T, PREFIX, NAME )                                    \
inline T NAME ( const long int *n                                     \
              , T *x, const long int *incx                            \
              , T *y, const long int *incy                            \
              )                                                       \
{                                                                     \
  return NT2_F77NAME(BOOST_PP_CAT(PREFIX,NAME))(n, x, incx, y, incy); \
}                                                                     \
/**/

  // INTERNAL ONLY
  // dot dotc dotu
  // FUNCTION   _DOT  ( N,         X, INCX, Y, INCY ) S, D, DS
  // FUNCTION   _DOTU ( N,         X, INCX, Y, INCY ) C, Z
  // FUNCTION   _DOTC ( N,         X, INCX, Y, INCY ) C, Z
  // FUNCTION   __DOT ( N,  ALPHA, X, INCX, Y, INCY ) SDS
  NT2_MISC(double, d, dot )
  NT2_MISC(float,  s, dot )
  NT2_MISC(std::complex<double>, z, dotu )
  NT2_MISC(std::complex<float>,  c, dotu )
  NT2_MISC(std::complex<double>, z, dotc )
  NT2_MISC(std::complex<float>,  c, dotc )

#undef NT2_MISC

#define NT2_MISC(T, PREFIX, NAME)                                   \
inline T NAME ( const long int *n                                   \
              , const T *alpha                                      \
              , T *x, const long int *incx                          \
              )                                                     \
{                                                                   \
  return NT2_F77NAME(BOOST_PP_CAT(PREFIX,NAME))(n, alpha, x, incx); \
}                                                                   \
/**/

  // INTERNAL ONLY
  // axpy
  // SUBROUTINE _AXPY ( N,  ALPHA, X, INCX, Y, INCY ) S, D, C, Z
  NT2_MISC(double, d, axpy)
  NT2_MISC(float,  s, axpy)
  NT2_MISC(std::complex<double>, z, axpy)
  NT2_MISC(std::complex<float>,  c, axpy)

#undef NT2_MISC

#define NT2_MISC(T, PREFIX, NAME, RET)                                        \
inline RET NAME ( const long int *n                                           \
                , const T *alpha                                              \
                , T *x, const long int *incx                                  \
                , T *y, const long int *incy                                  \
                )                                                             \
{                                                                             \
  return NT2_F77NAME(BOOST_PP_CAT(PREFIX,NAME))(n, alpha, x, incx, y, incy);  \
}                                                                             \

  // INTERNAL ONLY
  // nrm2
  // FUNCTION   _NRM2 ( N, X, INCX ) S, D, SC, DZ
  NT2_MISC(double, d, nrm2, double)
  NT2_MISC(float,  s, nrm2, float)
  NT2_MISC(std::complex<double>, z, nrm2, std::complex<double>)
  NT2_MISC(std::complex<float>,  c, nrm2, std::complex<float>)

  // INTERNAL ONLY
  // asum
  // FUNCTION   _ASUM( N, X, INCX ) S, D, SC, DZ
  NT2_MISC(double, d, asum, double)
  NT2_MISC(float,  s, asum, float)
  NT2_MISC(std::complex<double>, z, asum, std::complex<double>)
  NT2_MISC(std::complex<float>,  c, asum, std::complex<float)

  // INTERNAL ONLY
  // i_amax
  // FUNCTION   I_AMAX( N, X, INCX ) S, D, C, Z
  NT2_MISC(double, d, i_amax, long int)
  NT2_MISC(float,  s, i_amax, long int)
  NT2_MISC(std::complex<double>, z, i_amax, long int)
  NT2_MISC(std::complex<float>,  c, i_amax, long int)

#undef NT2_MISC
} }

#endif
