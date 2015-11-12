//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_POCON_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_POCON_HPP_INCLUDED

#include <complex>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

//         info is integer
//          = 0:  successful exit
//          < 0:  if info = -i, the i-th argument had an illegal value

extern "C"
{
  void NT2_F77NAME(cpocon)( const char* uplo        , const nt2_la_int* n
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , const float* anorm      , float* rcond
                          , nt2_la_complex* work    , float* rwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zpocon)( const char* uplo        , const nt2_la_int* n
                          , const nt2_la_complex* a , const nt2_la_int* lda
                          , const double* anorm     , double* rcond
                          , nt2_la_complex* work    , double* rwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(dpocon)( const char* uplo    , const nt2_la_int* n
                          , const double* a     , const nt2_la_int* lda
                          , const double* anorm , double* rcond
                          , double* work        , nt2_la_int* iwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(spocon)( const char* uplo  , const nt2_la_int* n
                          , const float* a    , const nt2_la_int* lda
                          , const float* anorm, float* rcond
                          , float* work       , nt2_la_int* iwork
                          , nt2_la_int* info
                          );
}

namespace nt2 { namespace details
{
#define NT2_POCON(NAME, T)                                                \
inline void pocon ( const char* uplo, const nt2_la_int* n                 \
                  , const T* a      , const nt2_la_int* lda               \
                  , const T* anorm  , T* rcond                            \
                  , nt2_la_int* info, workspace<T>& w                     \
                  )                                                       \
{                                                                         \
  w.resize_integers((*n));                                                \
  w.resize_main( 3*(*n) );                                                \
  NT2_F77NAME(NAME)(uplo,n,a,lda,anorm,rcond,w.main(),w.integers(),info); \
}                                                                         \
                                                                          \
inline void pocon ( const char* uplo, const nt2_la_int* n                 \
                  , const T* a      , const nt2_la_int* lda               \
                  , const T* anorm  , T* rcond                            \
                  , nt2_la_int* info                                      \
                  )                                                       \
{                                                                         \
  nt2::details::workspace<T> w;                                           \
  pocon(uplo, n, a, lda, anorm, rcond, info, w);                          \
}                                                                         \
/**/

  NT2_POCON(spocon, float)
  NT2_POCON(dpocon, double)

#undef NT2_POCON

#define NT2_POCON(NAME, T, B)                                           \
inline void pocon ( const char* uplo, const nt2_la_int* n               \
                  , const T* a      , const nt2_la_int* lda             \
                  , const B* anorm  , B* rcond                          \
                  , nt2_la_int* info, workspace<T> & w                  \
                  )                                                     \
{                                                                       \
  w.resize_reals((*n));                                                 \
  w.resize_main(2*(*n));                                                \
  NT2_F77NAME(NAME)(uplo,n,a,lda,anorm,rcond,w.main(),w.reals(),info);  \
}                                                                       \
                                                                        \
inline void pocon ( const char* uplo, const nt2_la_int* n               \
                  , const T* a      , const nt2_la_int* lda             \
                  , const B* anorm  , B* rcond                          \
                  , nt2_la_int* info                                    \
                  )                                                     \
{                                                                       \
  nt2::details::workspace<T> w;                                         \
  pocon(uplo, n, a, lda, anorm, rcond, info, w);                        \
}                                                                       \
/**/

  NT2_POCON(cpocon, std::complex<float> , float )
  NT2_POCON(zpocon, std::complex<double>, double)

#undef NT2_POCON
} }

#endif
