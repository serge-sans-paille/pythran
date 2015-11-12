//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GETRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GETRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2
{
  namespace details
  {
    extern "C"
    {
  void NT2_F77NAME(cgetrf)(const nt2_la_int* m, const nt2_la_int* n,
                       nt2_la_complex* a, const nt2_la_int* lda,
                       nt2_la_int* ipiv, nt2_la_int* info);
  void NT2_F77NAME(zgetrf)(const nt2_la_int* m, const nt2_la_int* n,
                       nt2_la_complex* a, const nt2_la_int* lda,
                       nt2_la_int* ipiv, nt2_la_int* info);
    }

#define NT2_GETRF(NAME, T)                      \
    inline void getrf(const nt2_la_int* m,      \
                      const nt2_la_int* n,      \
                      T* a,                     \
                      const nt2_la_int* lda,    \
                      nt2_la_int* ipiv,         \
                      nt2_la_int* info)         \
    {                                           \
      nt2::details::workspace<T> w;             \
      getrf(m, n, a, lda, ipiv, info, w);       \
    }                                           \

    NT2_GETRF(cgetrf, std::complex<float>)
    NT2_GETRF(zgetrf, std::complex<double>)

#undef NT2_GETRF
  }
}

#endif
