//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_HSEV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_HSEV_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/include/functions/scalar/max.hpp>
//    **  purpose
//     **  =======
//     **
//     **  xheev computes all eigenvalues and, optionally, eigenvectors of a
//     **  DATA TYPE hermitian matrix a.
//     **
//     **  arguments
//     **  =========
//     **
//     **  jobz    (input) char
//     **          = 'n':  compute eigenvalues only;
//     **          = 'v':  compute eigenvalues and eigenvectors.
//     **
//     **  uplo    (input) char
//     **          = 'u':  upper triangle of a is stored;
//     **          = 'l':  lower triangle of a is stored.
//     **
//     **  n       (input) long int
//     **          the order of the matrix a.  n >= 0.
//     **
//     **  a       (input/output) DATA TYPE array, dimension (lda, n)
//     **          on entry, the hermitian matrix a.  if uplo = 'u', the
//     **          leading n-by-n upper triangular part of a contains the
//     **          upper triangular part of the matrix a.  if uplo = 'l',
//     **          the leading n-by-n lower triangular part of a contains
//     **          the lower triangular part of the matrix a.
//     **          on exit, if jobz = 'v', then if info = 0, a contains the
//     **          orthonormal eigenvectors of the matrix a.
//     **          if jobz = 'n', then on exit the lower triangle (if uplo='l')
//     **          or the upper triangle (if uplo='u') of a, including the
//     **          diagonal, is destroyed.
//     **
//     **  lda     (input) long int
//     **          the leading dimension of the array a.  lda >= max(1,n).
//     **
//     **  w       (output) BASE DATA TYPE array, dimension (n)
//     **          if info = 0, the eigenvalues in ascending order.
//     **
//     **
//     **
//     **
//     **  info    (output) long int
//     **          = 0:  successful exit
//     **          < 0:  if info = -i, the i-th argument had an illegal value
//     **          > 0:  if info = i, the algorithm failed to converge; i
//     **                off-diagonal elements of an intermediate tridiagonal
//     **                form did not converge to zero.

namespace nt2 { namespace details
{
  extern "C"
  {
    void NT2_F77NAME(cheev)(const char* jobz, const char* uplo, const nt2_la_int* n,
                            nt2_la_complex* a, const nt2_la_int* lda, float* w, nt2_la_complex* work,
                            const nt2_la_int* lwork, float* rwork, nt2_la_int* info);
    void NT2_F77NAME(zheev)(const char* jobz, const char* uplo, const nt2_la_int* n,
                            nt2_la_complex* a, const nt2_la_int* lda, double* w, nt2_la_complex* work,
                            const nt2_la_int* lwork, double* rwork, nt2_la_int* info);
    void NT2_F77NAME(dsyev)(const char* jobz, const char* uplo, const nt2_la_int* n,
                            double* a, const nt2_la_int* lda, double* w, double* work,
                            const nt2_la_int* lwork, nt2_la_int* info);
    void NT2_F77NAME(ssyev)(const char* jobz, const char* uplo, const nt2_la_int* n,
                            float* a, const nt2_la_int* lda, float* w, float* work,
                            const nt2_la_int* lwork, nt2_la_int* info);
  }

#define NT2_HEEV(NAME, T, TBASE)                \
  inline void hsev(const char* jobz,            \
                   const char* uplo,            \
                   const nt2_la_int* n,         \
                   T* a,                        \
                   const nt2_la_int* lda,       \
                   TBASE* ws,                   \
                   nt2_la_int* info,            \
                   workspace<T> & w)            \
  {                                             \
    w.resize_reals(nt2::max(1, 3**n-2));        \
    NT2_F77NAME( NAME )(jobz, uplo, n,          \
                        a, lda, ws, w.main(),   \
                        query(), w.reals(),     \
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(jobz, uplo, n,          \
                        a, lda, ws, w.main(),   \
                        &wn, w.reals(),         \
                        info);                  \
  }                                             \
    inline void hsev(const char* jobz,          \
                     const char* uplo,          \
                     const nt2_la_int* n,       \
                     T* a,                      \
                     const nt2_la_int* lda,     \
                     TBASE* ws,                 \
                     nt2_la_int* info)          \
    {                                           \
      workspace<T> w;                           \
      hsev(jobz, uplo, n, a, lda,               \
           ws, info, w);                        \
    }                                           \
    /**/

  NT2_HEEV(cheev, std::complex<float>, float)
    NT2_HEEV(zheev, std::complex<double>, double)

#undef NT2_HEEV


#define NT2_SYEV(NAME, T)                       \
    inline void hsev(const char* jobz,          \
                     const char* uplo,          \
                     const nt2_la_int* n,       \
                     T* a,                      \
                     const nt2_la_int* lda,     \
                     T* ws,                     \
                     nt2_la_int* info,          \
                     workspace<T> & w)          \
    {                                           \
      NT2_F77NAME( NAME )(jobz, uplo, n,        \
                          a, lda,               \
                          ws, w.main(), query(),        \
                          info);                        \
      nt2_la_int wn = w.main_need();                    \
      w.resize_main(wn);                                \
      NT2_F77NAME( NAME )(jobz, uplo, n,                \
                          a, lda, ws, w.main(),         \
                          &wn, info);                   \
    }                                                   \
      inline void hsev(const char* jobz,                \
                       const char* uplo,                \
                       const nt2_la_int* n,             \
                       T* a,                            \
                       const nt2_la_int* lda,           \
                       T* ws,                           \
                       nt2_la_int* info)                \
      {                                                 \
        workspace<T> w;                                 \
        hsev(jobz, uplo, n, a, lda,                     \
             ws, info, w);                              \
      }                                                 \
      /**/

    NT2_SYEV(ssyev, float)
      NT2_SYEV(dsyev, double)

#undef NT2_SYEV

} }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of hsev.hpp
// /////////////////////////////////////////////////////////////////////////////
