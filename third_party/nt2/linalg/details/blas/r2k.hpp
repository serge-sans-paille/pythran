//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_R2K_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_R2K_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_R2K(T, PREFIX)                                            \
inline void syr2k ( const char *uplo, const long int *n               \
                  , const T *al                                       \
                  , const T *a, const long int *lda                   \
                  , const T *b, const long int *ldb                   \
                  , const T *be                                       \
                  , T *c      , const long int *ldc                   \
                  )                                                   \
{                                                                     \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,syr2k))(uplo,n,al,a,lda,be,c,ldc);  \
}                                                                     \
/**/

  // tA is the transpose of A
  // syr2k  C <- al*tA*B+al*B*tA+be*C or  C <- al*tA*B+A*tB+be*C (trans N, T)
  NT2_R2K(double, d)
  NT2_R2K(float,  s)
  NT2_R2K(std::complex<double>, z)
  NT2_R2K(std::complex<float>, c)

#undef NT2_R2K

#define NT2_R2K(T, PREFIX)                                            \
inline void her2k ( const char *uplo, const long int *n               \
                  , const T *al                                       \
                  , const T *a, const long int *lda                   \
                  , const T *b, const long int *ldb                   \
                  , const T *be                                       \
                  , T *c      , const long int *ldc                   \
                  )                                                   \
{                                                                     \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,her2k))(uplo,n,al,a,lda,be,c,ldc);  \
}                                                                     \
/**/

  // hA is the transconjugate of A
  // her2k  C <- al*hA*B+al*B*hA+be*C or  C <- al*hA*B+A*hB+be*C (trans N, C)
  NT2_R2K(std::complex<double>, z)
  NT2_R2K(std::complex<float>, c)

#undef NT2_R2K
} }

#endif
