//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_TRTRS_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_TRTRS_HPP_INCLUDED
// trtrs
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

extern "C"
{
  void NT2_F77NAME(ctrtrs)(const char* uplo, const char* trans, const char* diag,
                           const nt2_la_int* n, const nt2_la_int* nrhs,
                           const nt2_la_complex* a, const nt2_la_int* lda,
                           nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(dtrtrs)(const char* uplo, const char* trans, const char* diag,
                           const nt2_la_int* n, const nt2_la_int* nrhs,
                           const double* a, const nt2_la_int* lda,
                           double* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(strtrs)(const char* uplo, const char* trans, const char* diag,
                           const nt2_la_int* n, const nt2_la_int* nrhs,
                           const float* a, const nt2_la_int* lda,
                           float* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(ztrtrs)(const char* uplo, const char* trans, const char* diag,
                           const nt2_la_int* n, const nt2_la_int* nrhs,
                           const nt2_la_complex* a, const nt2_la_int* lda,
                           nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info);
}

namespace nt2
{
  namespace details
  {
#define NT2_TRTRS(NAME, T)                      \
    inline void trtrs(const char* uplo,         \
                      const char* trans,        \
                      const char* diag,         \
                      const nt2_la_int* n,      \
                      const nt2_la_int* nrhs,   \
                      const T* a,               \
                      const nt2_la_int* lda,    \
                      T* b,                     \
                      const nt2_la_int* ldb,    \
                      nt2_la_int* info)         \
    {                                           \
      NT2_F77NAME( NAME )(uplo,trans,diag,      \
                          n,nrhs,a,             \
                          lda, b,ldb,info);     \
    }                                           \


    NT2_TRTRS(strtrs, float)
    NT2_TRTRS(dtrtrs, double)
    NT2_TRTRS(ctrtrs, std::complex<float>)
    NT2_TRTRS(ztrtrs, std::complex<double>)

#undef NT2_TRTRS
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of trs.hpp
// /////////////////////////////////////////////////////////////////////////////
