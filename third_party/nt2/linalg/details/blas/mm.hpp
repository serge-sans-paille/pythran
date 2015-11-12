//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_MM_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_MM_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_MM(T, PX)                                                       \
inline void gemm( const char *ta, const char *tb                            \
                , const nt2_la_int *m, const nt2_la_int *n, const nt2_la_int *k \
                , const T *al                                               \
                , const T *a, const nt2_la_int *lda                         \
                , const T *b, const nt2_la_int *ldb                         \
                , const T *be                                               \
                , T *c      , const nt2_la_int *ldc                         \
                )                                                           \
{                                                                           \
  NT2_F77NAME(BOOST_PP_CAT(PX,gemm))(ta,tb,m,n,k,al,a,lda,b,ldb,be,c,ldc);  \
}                                                                           \
/**/

  // INTERNAL ONLY
  // GEMM variants
  // gemm C <- al*op(A)*op(B)+be*C (op t h n according ta and tb)
  NT2_MM(double, d)
  NT2_MM(float,  s)
  NT2_MM(std::complex<double>, z)
  NT2_MM(std::complex<float>, c)
#undef NT2_MM

#define NT2_MM(T, PX)                                                         \
inline void symm( const char *side, const char *uplo                          \
                , const nt2_la_int *m, const nt2_la_int *n                    \
                , const T *al                                                 \
                , const T *a, const nt2_la_int *lda                           \
                , const T *b, const nt2_la_int *ldb                           \
                , const T *be                                                 \
                , T *c      , const nt2_la_int *ldc                           \
                )                                                             \
{                                                                             \
  NT2_F77NAME(BOOST_PP_CAT(PX,symm))(side,uplo,m,n,al,a,lda,b,ldb,be,c,ldc);  \
}                                                                             \
/**/

  // INTERNAL ONLY
  // SYMM variants
  // symm C <- al*A*B +be+C or   al*B*A +be+C (A sy or he and according side)
  NT2_MM(double, d)
  NT2_MM(float,  s)
  NT2_MM(std::complex<double>, z)
  NT2_MM(std::complex<float>, c)

#undef NT2_MM

#define NT2_MM(T, PX)                                                         \
inline void hemm( const char *side, const char *uplo                          \
                , const nt2_la_int *m, const nt2_la_int *n                    \
                , const T *al                                                 \
                , const T *a, const nt2_la_int *lda                           \
                , const T *b, const nt2_la_int *ldb                           \
                , const T *be                                                 \
                , T *c      , const nt2_la_int *ldc                           \
                )                                                             \
{                                                                             \
  NT2_F77NAME(BOOST_PP_CAT(PX,hemm))(side,uplo,m,n,al,a,lda,b,ldb,be,c,ldc);  \
}                                                                             \
/**/

  // INTERNAL ONLY
  // HEMM variants
  // hemm C <- al*A*B +be+C or   al*B*A +be+C (A sy or he and according side)
  NT2_MM(std::complex<double>, z)
  NT2_MM(std::complex<float>, c)

#undef NT2_MM
} }

#endif
