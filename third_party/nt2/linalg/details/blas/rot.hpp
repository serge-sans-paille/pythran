//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_ROT_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_ROT_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_ROT(T, PREFIX)                                          \
inline void rotg( const T *a, const T *b, const T *c, const T *s )  \
{                                                                   \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,rotg))(a, b, c, s);               \
}                                                                   \
/**/

  // INTERNAL ONLY
  // rotg
  // SUBROUTINE _ROTG ( A, B, C, S ) S, D
  NT2_ROT(double, d )
  NT2_ROT(float,  s )

#undef NT2_ROT

#define NT2_ROT(T, PREFIX)                                  \
inline void rotmg ( const T *d1, const T *d2                \
                  , const T *a, const T *b, const T *param  \
                  )                                         \
{                                                           \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,rotmg))(d1,d2,a,b,param); \
}                                                           \
/**/

  // INTERNAL ONLY
  // rotmg
  // SUBROUTINE _ROTMG( D1, D2, A, B, PARAM ) S, D
  NT2_ROT(double, d, )
  NT2_ROT(float,  s, )
  NT2_ROT(std::complex<double>, z, u)
  NT2_ROT(std::complex<float>,  c, u)
  NT2_ROT(std::complex<double>, z, c)
  NT2_ROT(std::complex<float>,  c, c)

#undef NT2_ROT

#define NT2_ROT(T, PREFIX)                                          \
inline void rot ( const long int *n                                 \
                , const T *x, const long int *incx                  \
                , const T *y, const long int *incy                  \
                , const T *c, const T *s                            \
                )                                                   \
{                                                                   \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,rot))(n, x, incx, y, incy, c, s); \
}                                                                   \
/**/

  // INTERNAL ONLY
  // rotmg
  // SUBROUTINE _ROT  ( N, X, INCX, Y, INCY, C, S )   S, D
  NT2_ROT(double, d)
  NT2_ROT(float,  s)
#undef NT2_ROT

#define NT2_ROT(T, PREFIX)                                            \
inline void rotm( const long int *n,                                  \
                  const T *x, const long int *incx,                   \
                  const T *y, const long int *incy,                   \
                  const T *param                                      \
                )                                                     \
{                                                                     \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,rotm))(n, x, incx, y, incy, param); \
}                                                                     \
/**/

  // INTERNAL ONLY
  // rotm
  // SUBROUTINE _ROTM ( N, X, INCX, Y, INCY, PARAM )  S, D
  NT2_ROT(double, d)
  NT2_ROT(float,  s)
#undef NT2_ROT
} }

#endif
