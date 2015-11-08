//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_RK_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_RK_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_RK(T, PREFIX)                                           \
inline void syrk( const char *uplo, const long int *n               \
                , const T *al                                       \
                , const T *a, const long int *lda                   \
                , const T *be                                       \
                , T *c      , const long int *ldc                   \
                )                                                   \
{                                                                   \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,syrk))(uplo,n,al,a,lda,be,c,ldc); \
}                                                                   \
/**/

  // INTERNAL ONLY
  // tA is the transpose of A
  // syrk  C <- al*A*tA+be*C or  C <- al*tA*A+be*C (trans N, T)
  NT2_RK(double, d)
  NT2_RK(float,  s)
  NT2_RK(std::complex<double> , z )
  NT2_RK(std::complex<float>  , c )
#undef NT2_RK

#define NT2_RK(T, PREFIX)                                           \
inline void herk( const char *uplo, const long int *n               \
                , const T *al                                       \
                , const T *a, const long int *lda                   \
                , const T *be                                       \
                , T *c      , const long int *ldc                   \
                )                                                   \
{                                                                   \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,herk))(uplo,n,al,a,lda,be,c,ldc); \
}                                                                   \
/**/

  // INTERNAL ONLY
  // hA is the transconjugate of A
  // herk  C <- al*A*hA+be*C or  C <- al*A*hA+be*C (trans N, C)
  NT2_RK(std::complex<double>, z)
  NT2_RK(std::complex<float>, c)
#undef NT2_RK

} }

#endif
