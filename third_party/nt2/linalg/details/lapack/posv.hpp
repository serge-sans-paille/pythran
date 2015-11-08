//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_POSV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_POSV_HPP_INCLUDED

#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

extern "C"
{
  void NT2_F77NAME(cposv)(const char* uplo, const nt2_la_int* n, const nt2_la_int* nrhs,
                          nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                          nt2_la_int* info);
  void NT2_F77NAME(dposv)(const char* uplo, const nt2_la_int* n, const nt2_la_int* nrhs,
                          double* a, const nt2_la_int* lda, double* b, const nt2_la_int* ldb,
                          nt2_la_int* info);
  void NT2_F77NAME(sposv)(const char* uplo, const nt2_la_int* n, const nt2_la_int* nrhs,
                          float* a, const nt2_la_int* lda, float* b, const nt2_la_int* ldb,
                          nt2_la_int* info);
  void NT2_F77NAME(zposv)(const char* uplo, const nt2_la_int* n, const nt2_la_int* nrhs,
                          nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                          nt2_la_int* info);
}

namespace nt2
{
  namespace details
  {

#define NT2_POSV(NAME, T)                       \
    inline void posv(const char* uplo,          \
                     const nt2_la_int* n,       \
                     const nt2_la_int* nrhs,    \
                     T* a,                      \
                     const nt2_la_int* lda,     \
                     T* b,                      \
                     const nt2_la_int* ldb,     \
                     nt2_la_int* info)          \
    {                                           \
      NT2_F77NAME( NAME )(uplo,n,nrhs,          \
                          a,lda,b,ldb,info);    \
    }                                           \

    NT2_POSV(sposv, float)
    NT2_POSV(dposv, double)
    NT2_POSV(cposv, std::complex<float>)
    NT2_POSV(zposv, std::complex<double>)

#undef NT2_POSV


  }
}


#endif

