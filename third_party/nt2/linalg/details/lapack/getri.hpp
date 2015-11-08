//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GETRI_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GETRI_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
// trgetri

namespace nt2
{
  namespace details
  {
    extern "C"
    {
  void NT2_F77NAME(cgetri)(const nt2_la_int* n, nt2_la_complex* a, const nt2_la_int* lda,
                       const nt2_la_int* ipiv, nt2_la_complex* work, const nt2_la_int* lwork,
                       nt2_la_int* info);
  void NT2_F77NAME(zgetri)(const nt2_la_int* n, nt2_la_complex* a, const nt2_la_int* lda,
                       const nt2_la_int* ipiv, nt2_la_complex* work, const nt2_la_int* lwork,
                       nt2_la_int* info);
    }

#define NT2_GETRI(NAME, T)                      \
    inline void getri(const nt2_la_int* n,      \
                      T* a,                     \
                      const nt2_la_int* lda,    \
                      const nt2_la_int* ipiv,   \
                      nt2_la_int* info,         \
                      workspace<T> & w)         \
    {                                           \
      NT2_F77NAME(NAME)(n,a,lda,ipiv,           \
                        w.main(),query(),       \
                        info);                  \
      nt2_la_int wn =  w.main_need();           \
      w.resize_main(wn);                        \
      NT2_F77NAME(NAME)(n,a,lda,                \
                        ipiv,w.main(),          \
                        &wn, info);             \
    }                                           \
    inline void getri(const nt2_la_int* n,      \
                      T* a,                     \
                      const nt2_la_int* lda,    \
                      const nt2_la_int* ipiv,   \
                      nt2_la_int* info)         \
    {                                           \
      workspace<T> w;                           \
      getri(n, a, lda, ipiv, info, w);          \
    }                                           \


    NT2_GETRI(cgetri, std::complex<float>)
    NT2_GETRI(zgetri, std::complex<double>)

#undef NT2_GETRI
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of getri.hpp
// /////////////////////////////////////////////////////////////////////////////
