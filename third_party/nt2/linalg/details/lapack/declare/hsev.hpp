//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_HSEV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_HSEV_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

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

#endif
