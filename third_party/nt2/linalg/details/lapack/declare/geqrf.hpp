//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEQRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEQRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? C or Z
// *  Purpose
// *  =======
// *
// *  CGEQRF computes a QR factorization of a complex M-by-N matrix A:
// *  A = Q * R.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A.  M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) COMPLEX array, dimension (LDA,N)
// *          On entry, the M-by-N matrix A.
// *          On exit, the elements on and above the diagonal of the array
// *          contain the min(M,N)-by-N upper trapezoidal matrix R (R is
// *          upper triangular if m >= n); the elements below the diagonal,
// *          with the array TAU, represent the unitary matrix Q as a
// *          product of min(m,n) elementary reflectors (see Further
// *          Details).
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,M).
// *
// *  TAU     (output) COMPLEX array, dimension (min(M,N))
// *          The scalar factors of the elementary reflectors (see Further
// *          Details).
// *
// *  WORK    (workspace/output) COMPLEX array, dimension (MAX(1,LWORK))
// *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK.  LWORK >= max(1,N).
// *          For optimum performance LWORK >= N*NB, where NB is
// *          the optimal blocksize.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value
///////////////////////////////////////////////////////////////////////
/// FOR ? S or D
// *  Purpose
// *  =======
// *
// *  DGEQRF computes a QR factorization of a real M-by-N matrix A:
// *  A = Q * R.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A.  M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
// *          On entry, the M-by-N matrix A.
// *          On exit, the elements on and above the diagonal of the array
// *          contain the min(M,N)-by-N upper trapezoidal matrix R (R is
// *          upper triangular if m >= n); the elements below the diagonal,
// *          with the array TAU, represent the orthogonal matrix Q as a
// *          product of min(m,n) elementary reflectors (see Further
// *          Details).
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,M).
// *
// *  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))
// *          The scalar factors of the elementary reflectors (see Further
// *          Details).
// *
// *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK.  LWORK >= max(1,N).
// *          For optimum performance LWORK >= N*NB, where NB is
// *          the optimal blocksize.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value
// *
extern "C"

{
  void NT2_F77NAME(dgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , double* a               , const nt2_la_int* lda
                          , double* tau             , double* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );

  void NT2_F77NAME(sgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , float* a                , const nt2_la_int* lda
                          , float* tau              , float* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );

  void NT2_F77NAME(cgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , nt2_la_complex* a       , const nt2_la_int* lda
                          , nt2_la_complex* tau     , nt2_la_complex* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );

  void NT2_F77NAME(zgeqrf)( const nt2_la_int* m     , const nt2_la_int* n
                          , nt2_la_complex* a       , const nt2_la_int* lda
                          , nt2_la_complex* tau     , nt2_la_complex* work
                          , const nt2_la_int* lwork , nt2_la_int* info
                          );
}

#endif
