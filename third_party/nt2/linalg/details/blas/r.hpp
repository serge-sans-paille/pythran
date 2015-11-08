//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_R_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_R_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_R(T, PREFIX, SUFFIX)                                            \
inline void BOOST_PP_CAT(ger,SUFFIX)( const long int *m, const long int *n  \
                                    , const T *al                           \
                                    , const T *x, const long int *incx      \
                                    , const T *y, const long int *incy      \
                                    , const T *a, const long int *lda       \
                                    )                                       \
{                                                                           \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,ger))(ta,m,n,al,x,incx,y,incy,a,lda);     \
}                                                                           \
/**/

  // INTERNAL ONLY
  // gerx A <- {t,c}x*y+A  with x =  u, c or nothing in which case x == y
  // _GER  ( M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) S, D
  // _GERU ( M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z (TRANSPOSE)
  // _GERC ( M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z (TRANSCONJUGATE)
  NT2_R(double, d, )
  NT2_R(float,  s, )
  NT2_R(std::complex<double>, z, u)
  NT2_R(std::complex<float>,  c, u)
  NT2_R(std::complex<double>, z, c)
  NT2_R(std::complex<float>,  c, c)

#undef NT2_R

#define NT2_R(T, P1, P2)                                                  \
inline void BOOST_PP_CAT(P2,r)( const char * uplo                         \
                              , const long int *n                         \
                              , const T *al                               \
                              , const T *x, const long int *incx          \
                              , T *a      , const long int *lda           \
                              )                                           \
{                                                                         \
  NT2_F77NAME(BOOST_PP_CAT(P1,BOOST_PP_CAT(P2,r)))(ta,n,al,x,incx,a,lda); \
}                                                                         \
/**/

  // INTERNAL ONLY
  // herx A <- hx*y+hy*x+A
  // syrx A <- tx*y+ty*x+A
  // _HER  ( UPLO, N, ALPHA, X, INCX, A, LDA ) C, Z
  // _SYR  ( UPLO, N, ALPHA, X, INCX, A, LDA ) S, D
  NT2_R(std::complex<double>, z, he)
  NT2_R(std::complex<float>,  c, he)
  NT2_R(std::complex<double>, s, sy)
  NT2_R(std::complex<float>,  d, sy)
#undef NT2_R

#define NT2_R(T, P1, P2)                                                    \
inline void BOOST_PP_CAT(P2,r)( const char * uplo                           \
                              , const long int *n                           \
                              , const T *al                                 \
                              , const T *x, const long int *incx            \
                              , T *ap                                       \
                              )                                             \
{                                                                           \
  BOOST_PP_CAT(BOOST_PP_CAT(P1,BOOST_PP_CAT(P2,r),_))(uplo,n,al,x,incx,ap); \
}                                                                           \
/**/

  // INTERNAL ONLY
  // herx A <- hx*y+hy*x+A
  // syrx A <- tx*y+ty*x+A
  // _HER  ( UPLO, N, ALPHA, X, INCX, A, LDA ) C, Z
  // _SYR  ( UPLO, N, ALPHA, X, INCX, A, LDA ) S, D
  NT2_R(std::complex<double>, z, hp)
  NT2_R(std::complex<float>,  c, hp)
  NT2_R(std::complex<double>, s, sp)
  NT2_R(std::complex<float>,  d, sp)
#undef NT2_R

#define NT2_R(T, P1, P2)                                                          \
inline void BOOST_PP_CAT(P2,r2) ( const char * uplo                               \
                                , const long int *n                               \
                                , const T *al                                     \
                                , const T *x, const long int *ix                  \
                                , const T *y, const long int *iy                  \
                                , T *a, const long int *lda                       \
                                )                                                 \
{                                                                                 \
  BOOST_PP_CAT(BOOST_PP_CAT(P1,BOOST_PP_CAT(P2,r2),_)(uplo,n,al,x,ix,y,iy,a,lda); \
}                                                                                 \
/**/

  // INTERNAL ONLY
  // _HER2 ( UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA )
  // _SYR2 ( UPLO, N, ALPHA, X, INCX, Y, INCY, A, LDA )
  NT2_R(std::complex<double>, z, he)
  NT2_R(std::complex<float>,  c, he)
  NT2_R(std::complex<double>, s, sy)
  NT2_R(std::complex<float>,  d, sy)
#undef NT2_R

#define NT2_R(T, P1, P2)                                                      \
inline void BOOST_PP_CAT(P2,r)( const char * uplo                             \
                              , const long int *n                             \
                              , const T *al                                   \
                              , const T *x, const long int *incx              \
                              , T *ap                                         \
                              )                                               \
{                                                                             \
  BOOST_PP_CAT(BOOST_PP_CAT(P1,BOOST_PP_CAT(P2,r2),_))(uplo,n,al,x,incx,ap);  \
}                                                                             \
/**/

  // INTERNAL ONLY
  // _HPR  ( UPLO, N, ALPHA, X, INCX, AP )
  // _SPR  ( UPLO, N, ALPHA, X, INCX, AP )
  NT2_R(std::complex<double>, z, hp)
  NT2_R(std::complex<float>,  c, hp)
  NT2_R(std::complex<double>, s, sp)
  NT2_R(std::complex<float>,  d, sp)
#undef NT2_R
} }

#endif
