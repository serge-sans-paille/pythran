//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_MQR_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_MQR_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

// its a mix or ormqr and unmqr
// DORMQR overwrites the general real M-by-N matrix C with
// *
// *                  SIDE = 'L'     SIDE = 'R'
// *  TRANS = 'N':      Q * C          C * Q
// *  TRANS = 'T':      Q**T * C       C * Q**T
// *
// *  where Q is a real orthogonal matrix defined as the product of k
// *  elementary reflectors
// *
// *        Q = H(1) H(2) . . . H(k)
// *
// *  as returned by DGEQRF. Q is of order M if SIDE = 'L' and of order N
// *  if SIDE = 'R'.
// *
// *  Arguments
// *  =========
// *
// *  SIDE    (input) CHARACTER*1
// *          = 'L': apply Q or Q**T from the Left;
// *          = 'R': apply Q or Q**T from the Right.
// *
// *  TRANS   (input) CHARACTER*1
// *          = 'N':  No transpose, apply Q;
// *          = 'T':  Transpose, apply Q**T.
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix C. M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix C. N >= 0.
// *
// *  K       (input) INTEGER
// *          The number of elementary reflectors whose product defines
// *          the matrix Q.
// *          If SIDE = 'L', M >= K >= 0;
// *          if SIDE = 'R', N >= K >= 0.
// *
// *  A       (input) DOUBLE PRECISION array, dimension (LDA,K)
// *          The i-th column must contain the vector which defines the
// *          elementary reflector H(i), for i = 1,2,...,k, as returned by
// *          DGEQRF in the first k columns of its array argument A.
// *          A is modified by the routine but restored on exit.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.
// *          If SIDE = 'L', LDA >= max(1,M);
// *          if SIDE = 'R', LDA >= max(1,N).
// *
// *  TAU     (input) DOUBLE PRECISION array, dimension (K)
// *          TAU(i) must contain the scalar factor of the elementary
// *          reflector H(i), as returned by DGEQRF.
// *
// *  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)
// *          On entry, the M-by-N matrix C.
// *          On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q.
// *
// *  LDC     (input) INTEGER
// *          The leading dimension of the array C. LDC >= max(1,M).
// *
// *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK.
// *          If SIDE = 'L', LWORK >= max(1,N);
// *          if SIDE = 'R', LWORK >= max(1,M).
// *          For optimum performance LWORK >= N*NB if SIDE = 'L', and
// *          LWORK >= M*NB if SIDE = 'R', where NB is the optimal
// *          blocksize.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value
extern "C"
{
  void NT2_F77NAME(sormqr)(const char* side, const char* trans,
                           const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           const float* a, const nt2_la_int* lda,
                           const float* tau, float* c, const nt2_la_int* ldc,
                           float* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(dormqr)(const char* side, const char* trans,
                           const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           const double* a, const nt2_la_int* lda,
                           const double* tau, double* c, const nt2_la_int* ldc,
                           double* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(zunmqr)(const char* side, const char* trans,
                           const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           const nt2_la_complex* a, const nt2_la_int* lda,
                           const nt2_la_complex* tau, nt2_la_complex* c, const nt2_la_int* ldc,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(cunmqr)(const char* side, const char* trans,
                           const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           const nt2_la_complex* a, const nt2_la_int* lda,
                           const nt2_la_complex* tau, nt2_la_complex* c, const nt2_la_int* ldc,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
}

#endif
