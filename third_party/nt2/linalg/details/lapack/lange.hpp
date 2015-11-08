//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_LANGE_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_LANGE_HPP_INCLUDED

#include <complex>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  double NT2_F77NAME(dlange)( const char* norm
                            , const nt2_la_int* m , const nt2_la_int* n
                            , const double* a     , const nt2_la_int* lda
                            , double* work
                            );

  float NT2_F77NAME(slange) ( const char* norm
                            , const nt2_la_int* m , const nt2_la_int* n
                            , const float* a      , const nt2_la_int* lda
                            , float* work
                            );

  float NT2_F77NAME(zlange) ( const char* norm
                            , const nt2_la_int* m     , const nt2_la_int* n
                            , const nt2_la_complex* a , const nt2_la_int* lda
                            , double* work
                            );

  float NT2_F77NAME(clange) ( const char* norm
                            , const nt2_la_int* m     , const nt2_la_int* n
                            , const nt2_la_complex* a , const nt2_la_int* lda
                            , float* work
                            );
}

namespace nt2 { namespace details
{
#define NT2_LANGE(NAME, T, B)                                 \
inline B lange( const char* norm                              \
              , const nt2_la_int* m , const nt2_la_int* n     \
              , const T* a          , const nt2_la_int* lda   \
              , nt2::details::workspace<T>& w                 \
              )                                               \
{                                                             \
  w.resize_reals((((*norm)=='i')||((*norm)=='I')) ? *n : 0 ); \
  return NT2_F77NAME(NAME)(norm, m, n, a, lda, w.reals());    \
}                                                             \
                                                              \
inline B lange( const char* norm                              \
              , const nt2_la_int* m , const nt2_la_int* n     \
              , const T* a          , const nt2_la_int* lda   \
              )                                               \
{                                                             \
  nt2::details::workspace<T> w;                               \
  return lange(norm, m, n, a, lda, w);                        \
}                                                             \
/**/

  NT2_LANGE(slange, float               , float )
  NT2_LANGE(dlange, double              , double)
  NT2_LANGE(clange, std::complex<float> , float )
  NT2_LANGE(zlange, std::complex<double>, double)

#undef NT2_LANGE

} }

#endif
