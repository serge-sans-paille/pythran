//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_MV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_MV_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas2.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_MV(T, PX)                                                   \
inline void gemv( const char *ta                                        \
                , const nt2_la_int *m, const nt2_la_int *n              \
                , const T *al                                           \
                , const T *a, const nt2_la_int *lda                     \
                , const T *x, const nt2_la_int *incx                    \
                , const T *be                                           \
                , T *y      , const nt2_la_int *incy                    \
                )                                                       \
{                                                                       \
  NT2_F77NAME(BOOST_PP_CAT(PX,gemv))(ta,m,n,al,a,lda,x,incx,be,y,incy); \
}                                                                       \
/**/

  // INTERNAL ONLY
  // gemv binding for all types
  // _GEMV (TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY )
  NT2_MV(double, d)
  NT2_MV(float,  s)
  NT2_MV(std::complex<double>, z)
  NT2_MV(std::complex<float>, c)

#undef NT2_MV

#define NT2_MV(T, PX)                                                         \
inline void gbmv( const char *ta                                              \
                , const nt2_la_int *m, const nt2_la_int *n                    \
                , const nt2_la_int *kl, const nt2_la_int *ku                  \
                , const T *al                                                 \
                , const T *a, const nt2_la_int *lda                           \
                , const T *x, const nt2_la_int *incx                          \
                , const T *be                                                 \
                , T *y      , const nt2_la_int *incy                          \
                )                                                             \
{                                                                             \
  NT2_F77NAME(BOOST_PP_CAT(PX,gbmv))(ta,m,n,kl,ku,al,a,lda,x,incx,be,y,incy); \
}                                                                             \
/**/

  // INTERNAL ONLY
  // gbmv binding for all types
  // _GBMV(TRANS, M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA, Y, INCY )
  NT2_MV(double, d)
  NT2_MV(float,  s)
  NT2_MV(std::complex<double>, z)
  NT2_MV(std::complex<float>, c)

#undef NT2_MV

#define NT2_MV(T, P, Q)                                                             \
inline void BOOST_PP_CAT(Q,mv)( const char *uplo, const nt2_la_int *n               \
                              , const T *al                                         \
                              , const T *a, const nt2_la_int *lda                   \
                              , const T *x, const nt2_la_int *incx                  \
                              , const T *be                                         \
                              , T *y      , const nt2_la_int *incy                  \
                              )                                                     \
{                                                                                   \
  NT2_F77NAME(BOOST_PP_CAT(P,BOOST_PP_CAT(Q,mv)))(uplo,n,al,a,lda,x,incx,be,y,incy);  \
}                                                                                   \
/**/

  //  INTERNAL ONLY
  // *mv binging for hermittian/symmetric cases
  // _HEMV ( UPLO, N, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY )
  // _SYMV ( UPLO, N, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY )
  NT2_MV(std::complex<double>, z, he)
  NT2_MV(std::complex<float>, c, he)
  NT2_MV(double, d, sy)
  NT2_MV(float,  s, sy)

#undef NT2_MV

#define NT2_MV(T, P, Q)                                                               \
inline void BOOST_PP_CAT(Q,mv)( const char *uplo                                      \
                              , const nt2_la_int *n, const nt2_la_int *k              \
                              , const T *al                                           \
                              , const T *a, const nt2_la_int *lda                     \
                              , const T *x, const nt2_la_int *incx                    \
                              , const T *be                                           \
                              , T *y      , const nt2_la_int *incy                    \
                              )                                                       \
{                                                                                     \
  NT2_F77NAME(BOOST_PP_CAT(P,BOOST_PP_CAT(Q,mv)))(uplo,n,k,al,a,lda,x,incx,be,y,incy); \
}                                                                                     \
/**/

  // _HBMV ( UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY )
  // _SBMV ( UPLO, N, K, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY )
  NT2_MV(std::complex<double>, z, hb)
  NT2_MV(std::complex<float>, c, hb)
  NT2_MV(double, d, sb)
  NT2_MV(float,  s, sb)

#undef NT2_MV

#define NT2_MV(T, P, Q)                                                         \
inline void BOOST_PP_CAT(Q,mv)( const char *uplo, const nt2_la_int *n           \
                              , const T *al , const T *ap                       \
                              , const T *x  , const nt2_la_int *incx            \
                              , const T *be                                     \
                              , T *y        , const nt2_la_int *incy            \
                              )                                                 \
{                                                                               \
  NT2_F77NAME(BOOST_PP_CAT(P,BOOST_PP_CAT(Q,mv)))(uplo,n,al,ap,x,incx,be,y,incy); \
}                                                                               \
/**/

  // _HPMV ( UPLO N, ALPHA, AP, X, INCX, BETA,  Y, INCY )
  // _SPMV ( UPLO N, ALPHA, AP, X, INCX, BETA,  Y, INCY )
  NT2_MV(std::complex<double> , z, hp )
  NT2_MV(std::complex<float>  , c, hp )
  NT2_MV(double, d, sp)
  NT2_MV(float,  s, sp)

#undef NT2_MV

#define NT2_MV(T, P)                                                    \
inline void tpmv( const char *uplo, const char *trans, const char *diag \
                , const nt2_la_int *n                                   \
                , const T *ap                                           \
                , T *x, const nt2_la_int *incx                          \
                )                                                       \
{                                                                       \
  NT2_F77NAME(BOOST_PP_CAT(P,tpmv))(uplo,trans,diag,n,ap,x,incx);       \
}                                                                       \
/**/

  // _TPMV ( UPLO, TRANS, DIAG, N, A, LDA, X, INCX )
  NT2_MV(double, d)
  NT2_MV(float,  s)
  NT2_MV(std::complex<double> , z )
  NT2_MV(std::complex<float>  , c )

#undef NT2_MV

#define NT2_MV(T, P)                                                    \
inline void trmv( const char *uplo, const char *trans, const char *diag \
                , const nt2_la_int *n                                   \
                , const T *a, const nt2_la_int *lda                     \
                , T *x      , const nt2_la_int *incx                    \
                )                                                       \
{                                                                       \
  NT2_F77NAME(BOOST_PP_CAT(P,trmv))(uplo,trans,diag,n,a,lda,x,incx);    \
}                                                                       \
/**/

  // _TRMV ( UPLO, TRANS, DIAG, N, AP, X, INCX )
  NT2_MV(double, d)
  NT2_MV(float,  s)
  NT2_MV(std::complex<double> , z )
  NT2_MV(std::complex<float>  , c )
#undef NT2_MV

#define NT2_MV(T, P)                                                    \
inline void tbmv( const char *uplo, const char *trans, const char *diag \
                , const nt2_la_int *n,  const nt2_la_int *k             \
                , const T *a, const nt2_la_int *lda                     \
                , T *x      , const nt2_la_int *incx                    \
                )                                                       \
{                                                                       \
  NT2_F77NAME(BOOST_PP_CAT(P,tbmv))(uplo,trans,diag,n,k, a,lda,x,incx); \
}                                                                       \
/**/

  // _TBMV ( UPLO, TRANS, DIAG, N, K, A, LDA, X, INCX )
  NT2_MV(double, d)
  NT2_MV(float,  s)
  NT2_MV(std::complex<double>, z)
  NT2_MV(std::complex<float>, c)

#undef NT2_MV
} }

#endif
