//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEQP3_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEQP3_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? C or Z
// *  Purpose
// *  =======
// *
// *  CGEQP3 computes a QR factorization with column pivoting of a
// *  matrix A:  A*P = Q*R  using Level 3 BLAS.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A. M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) COMPLEX array, dimension (LDA,N)
// *          On entry, the M-by-N matrix A.
// *          On exit, the upper triangle of the array contains the
// *          min(M,N)-by-N upper trapezoidal matrix R; the elements below
// *          the diagonal, together with the array TAU, represent the
// *          unitary matrix Q as a product of min(M,N) elementary
// *          reflectors.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A. LDA >= max(1,M).
// *
// *  JPVT    (input/output) INTEGER array, dimension (N)
// *          On entry, if JPVT(J).ne.0, the J-th column of A is permuted
// *          to the front of A*P (a leading column); if JPVT(J)=0,
// *          the J-th column of A is a free column.
// *          On exit, if JPVT(J)=K, then the J-th column of A*P was the
// *          the K-th column of A.
// *
// *  TAU     (output) COMPLEX array, dimension (min(M,N))
// *          The scalar factors of the elementary reflectors.
// *
// *  WORK    (workspace/output) COMPLEX array, dimension (MAX(1,LWORK))
// *          On exit, if INFO=0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK. LWORK >= N+1.
// *          For optimal performance LWORK >= ( N+1 )*NB, where NB
// *          is the optimal blocksize.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  RWORK   (workspace) REAL array, dimension (2*N)
// *
// *  INFO    (output) INTEGER
// *          = 0: successful exit.
// *          < 0: if INFO = -i, the i-th argument had an illegal value.
// *
// *                to solve a system of equations.
///////////////////////////////////////////////////////////////////////
/// FOR ? S or D
// *  Purpose
// *  =======
// *
// *  DGEQP3 computes a QR factorization with column pivoting of a
// *  matrix A:  A*P = Q*R  using Level 3 BLAS.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A. M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
// *          On entry, the M-by-N matrix A.
// *          On exit, the upper triangle of the array contains the
// *          min(M,N)-by-N upper trapezoidal matrix R; the elements below
// *          the diagonal, together with the array TAU, represent the
// *          orthogonal matrix Q as a product of min(M,N) elementary
// *          reflectors.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A. LDA >= max(1,M).
// *
// *  JPVT    (input/output) INTEGER array, dimension (N)
// *          On entry, if JPVT(J).ne.0, the J-th column of A is permuted
// *          to the front of A*P (a leading column); if JPVT(J)=0,
// *          the J-th column of A is a free column.
// *          On exit, if JPVT(J)=K, then the J-th column of A*P was the
// *          the K-th column of A.
// *
// *  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))
// *          The scalar factors of the elementary reflectors.
// *
// *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// *          On exit, if INFO=0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK. LWORK >= 3*N+1.
// *          For optimal performance LWORK >= 2*N+( N+1 )*NB, where NB
// *          is the optimal blocksize.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  INFO    (output) INTEGER
// *          = 0: successful exit.
// *          < 0: if INFO = -i, the i-th argument had an illegal value.
// *
extern "C"

{
  void NT2_F77NAME(dgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , double* a            , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , double* tau
                          , double* work         , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(sgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , float* a             , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , float* tau
                          , float* work          , const nt2_la_int* lwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(cgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , nt2_la_complex* a    , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , nt2_la_complex* tau
                          , nt2_la_complex* work , const nt2_la_int* lwork
                          , float* rwork         , nt2_la_int* info
                          );

  void NT2_F77NAME(zgeqp3)( const nt2_la_int* m  , const nt2_la_int* n
                          , nt2_la_complex* a    , const nt2_la_int* lda
                          , nt2_la_int* jpvt     , nt2_la_complex* tau
                          , nt2_la_complex* work , const nt2_la_int* lwork
                          , double* rwork        , nt2_la_int* info
                          );
}

#endif
