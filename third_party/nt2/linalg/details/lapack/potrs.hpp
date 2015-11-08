//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_POTRS_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_POTRS_HPP_INCLUDED

#include <complex>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(cpotrs)( const char* uplo
                          , const long int* n, const long int* nrhs
                          , const nt2_la_complex* a, const long int* lda
                          , nt2_la_complex* b, const long int* ldb
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zpotrs)( const char* uplo
                          , const long int* n, const long int* nrhs
                          , const nt2_la_complex* a, const long int* lda
                          , nt2_la_complex* b, const long int* ldb
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(dpotrs)( const char* uplo
                          , const long int* n, const long int* nrhs
                          , const double* a, const long int* lda
                          , double* b, const long int* ldb
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(spotrs)( const char* uplo
                          , const long int* n, const long int* nrhs
                          , const float* a, const long int* lda
                          , float* b, const long int* ldb
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace details
{
#define NT2_POTRS(NAME, T)                                  \
inline void potrs ( const char* uplo                        \
                  , const long int* n, const long int* nrhs \
                  , const T* a, const long int* lda         \
                  , T* b, const long int* ldb               \
                  , nt2_la_int* info                        \
                  )                                         \
{                                                           \
  NT2_F77NAME(NAME)(uplo, n, nrhs, a, lda, b, ldb, info);   \
}                                                           \
/**/

  NT2_POTRS(spotrs, float)
  NT2_POTRS(dpotrs, double)
  NT2_POTRS(cpotrs, std::complex<float>)
  NT2_POTRS(zpotrs, std::complex<double>)

#undef NT2_POTRS
} }
#endif
