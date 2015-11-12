//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEESX_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEESX_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

// geesx
// >
// > \verbatim
// >
// > DGEESX computes for an N-by-N real nonsymmetric matrix A, the
// > eigenvalues, the real Schur form T, and, optionally, the matrix of
// > Schur vectors Z.  This gives the Schur factorization A = Z*T*(Z**T).
// >
// > Optionally, it also orders the eigenvalues on the diagonal of the
// > real Schur form so that selected eigenvalues are at the top left;
// > computes a reciprocal condition number for the average of the
// > selected eigenvalues (RCONDE); and computes a reciprocal condition
// > number for the right invariant subspace corresponding to the
// > selected eigenvalues (RCONDV).  The leading columns of Z form an
// > orthonormal basis for this invariant subspace.
// >
// > For further explanation of the reciprocal condition numbers RCONDE
// > and RCONDV, see Section 4.10 of the LAPACK Users' Guide (where
// > these quantities are called s and sep respectively).
// >
// > A real matrix is in real Schur form if it is upper quasi-triangular
// > with 1-by-1 and 2-by-2 blocks. 2-by-2 blocks will be standardized in
// > the form
// >           [  a  b  ]
// >           [  c  a  ]
// >
// > where b*c < 0. The eigenvalues of such a block are a +- sqrt(bc).
// > \endverbatim

//   Arguments:
//   ==========

// > \param[in] JOBVS
// > \verbatim
// >          JOBVS is CHARACTER*1
// >          = 'N': Schur vectors are not computed;
// >          = 'V': Schur vectors are computed.
// > \endverbatim
// >
// > \param[in] SORT
// > \verbatim
// >          SORT is CHARACTER*1
// >          Specifies whether or not to order the eigenvalues on the
// >          diagonal of the Schur form.
// >          = 'N': Eigenvalues are not ordered;
// >          = 'S': Eigenvalues are ordered (see SELECT).
// > \endverbatim
// >
// > \param[in] SELECT
// > \verbatim
// >          SELECT is procedure) LOGICAL FUNCTION of two DOUBLE PRECISION arguments
// >          SELECT must be declared EXTERNAL in the calling subroutine.
// >          If SORT = 'S', SELECT is used to select eigenvalues to sort
// >          to the top left of the Schur form.
// >          If SORT = 'N', SELECT is not referenced.
// >          An eigenvalue WR(j)+sqrt(-1)*WI(j) is selected if
// >          SELECT(WR(j),WI(j)) is true; i.e., if either one of a
// >          complex conjugate pair of eigenvalues is selected, then both
// >          are.  Note that a selected complex eigenvalue may no longer
// >          satisfy SELECT(WR(j),WI(j)) = .TRUE. after ordering, since
// >          ordering may change the value of complex eigenvalues
// >          (especially if the eigenvalue is ill-conditioned); in this
// >          case INFO may be set to N+3 (see INFO below).
// > \endverbatim
// >
// > \param[in] SENSE
// > \verbatim
// >          SENSE is CHARACTER*1
// >          Determines which reciprocal condition numbers are computed.
// >          = 'N': None are computed;
// >          = 'E': Computed for average of selected eigenvalues only;
// >          = 'V': Computed for selected right invariant subspace only;
// >          = 'B': Computed for both.
// >          If SENSE = 'E', 'V' or 'B', SORT must equal 'S'.
// > \endverbatim
// >
// > \param[in] N
// > \verbatim
// >          N is INTEGER
// >          The order of the matrix A. N >= 0.
// > \endverbatim
// >
// > \param[in,out] A
// > \verbatim
// >          A is DOUBLE PRECISION array, dimension (LDA, N)
// >          On entry, the N-by-N matrix A.
// >          On exit, A is overwritten by its real Schur form T.
// > \endverbatim
// >
// > \param[in] LDA
// > \verbatim
// >          LDA is INTEGER
// >          The leading dimension of the array A.  LDA >= max(1,N).
// > \endverbatim
// >
// > \param[out] SDIM
// > \verbatim
// >          SDIM is INTEGER
// >          If SORT = 'N', SDIM = 0.
// >          If SORT = 'S', SDIM = number of eigenvalues (after sorting)
// >                         for which SELECT is true. (Complex conjugate
// >                         pairs for which SELECT is true for either
// >                         eigenvalue count as 2.)
// > \endverbatim
// >
// > \param[out] WR
// > \verbatim
// >          WR is DOUBLE PRECISION array, dimension (N)
// > \endverbatim
// >
// > \param[out] WI
// > \verbatim
// >          WI is DOUBLE PRECISION array, dimension (N)
// >          WR and WI contain the real and imaginary parts, respectively,
// >          of the computed eigenvalues, in the same order that they
// >          appear on the diagonal of the output Schur form T.  Complex
// >          conjugate pairs of eigenvalues appear consecutively with the
// >          eigenvalue having the positive imaginary part first.
// > \endverbatim
// >
// > \param[out] VS
// > \verbatim
// >          VS is DOUBLE PRECISION array, dimension (LDVS,N)
// >          If JOBVS = 'V', VS contains the orthogonal matrix Z of Schur
// >          vectors.
// >          If JOBVS = 'N', VS is not referenced.
// > \endverbatim
// >
// > \param[in] LDVS
// > \verbatim
// >          LDVS is INTEGER
// >          The leading dimension of the array VS.  LDVS >= 1, and if
// >          JOBVS = 'V', LDVS >= N.
// > \endverbatim
// >
// > \param[out] RCONDE
// > \verbatim
// >          RCONDE is DOUBLE PRECISION
// >          If SENSE = 'E' or 'B', RCONDE contains the reciprocal
// >          condition number for the average of the selected eigenvalues.
// >          Not referenced if SENSE = 'N' or 'V'. <
// > \endverbatim
// >
// > \param[out] RCONDV
// > \verbatim
// >          RCONDV is DOUBLE PRECISION
// >          If SENSE = 'V' or 'B', RCONDV contains the reciprocal
// >          condition number for the selected right invariant subspace.
// >          Not referenced if SENSE = 'N' or 'E'.
// > \endverbatim
// >
// > \param[out] WORK
// > \verbatim
// >          WORK is DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// >          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// > \endverbatim
// >
// > \param[in] LWORK
// > \verbatim
// >          LWORK is INTEGER
// >          The dimension of the array WORK.  LWORK >= max(1,3*N).
// >          Also, if SENSE = 'E' or 'V' or 'B',
// >          LWORK >= N+2*SDIM*(N-SDIM), where SDIM is the number of
// >          selected eigenvalues computed by this routine.  Note that
// >          N+2*SDIM*(N-SDIM) <= N+N*N/2. Note also that an error is only
// >          returned if LWORK < max(1,3*N), but if SENSE = 'E' or 'V' or
// >          'B' this may not be large enough.
// >          For good performance, LWORK must generally be larger.
// >
// >          If LWORK = -1, then a workspace query is assumed; the routine
// >          only calculates upper bounds on the optimal sizes of the
// >          arrays WORK and IWORK, returns these values as the first
// >          entries of the WORK and IWORK arrays, and no error messages
// >          related to LWORK or LIWORK are issued by XERBLA.
// > \endverbatim
// >
// > \param[out] IWORK
// > \verbatim
// >          IWORK is INTEGER array, dimension (MAX(1,LIWORK))
// >          On exit, if INFO = 0, IWORK(1) returns the optimal LIWORK.
// > \endverbatim
// >
// > \param[in] LIWORK
// > \verbatim
// >          LIWORK is INTEGER
// >          The dimension of the array IWORK.
// >          LIWORK >= 1; if SENSE = 'V' or 'B', LIWORK >= SDIM*(N-SDIM).
// >          Note that SDIM*(N-SDIM) <= N*N/4. Note also that an error is
// >          only returned if LIWORK < 1, but if SENSE = 'V' or 'B' this
// >          may not be large enough.
// >
// >          If LIWORK = -1, then a workspace query is assumed; the
// >          routine only calculates upper bounds on the optimal sizes of
// >          the arrays WORK and IWORK, returns these values as the first
// >          entries of the WORK and IWORK arrays, and no error messages
// >          related to LWORK or LIWORK are issued by XERBLA.
// > \endverbatim
// >
// > \param[out] BWORK
// > \verbatim
// >          BWORK is LOGICAL array, dimension (N)
// >          Not referenced if SORT = 'N'.
// > \endverbatim
// >
// > \param[out] INFO
// > \verbatim
// >          INFO is INTEGER
// >          = 0: successful exit
// >          < 0: if INFO = -i, the i-th argument had an illegal value.
// >          > 0: if INFO = i, and i is
// >             <= N: the QR algorithm failed to compute all the
// >                   eigenvalues; elements 1:ILO-1 and i+1:N of WR and WI
// >                   contain those eigenvalues which have converged; if
// >                   JOBVS = 'V', VS contains the transformation which
// >                   reduces A to its partially converged Schur form.
// >             = N+1: the eigenvalues could not be reordered because some
// >                   eigenvalues were too close to separate (the problem
// >                   is very ill-conditioned);
// >             = N+2: after reordering, roundoff changed values of some
// >                   complex eigenvalues so that leading eigenvalues in
// >                   the Schur form no longer satisfy SELECT=.TRUE.  This
// >                   could also be caused by underflow due to scaling.
// > \endverbatim

extern "C"
{
  void NT2_F77NAME(cgeesx)(const char* jobvs, const char* sort, nt2::details::selectall_t* select, const char* sense,
                           const nt2_la_int* n, nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* sdim, nt2_la_complex* w,
                           const nt2_la_complex* vs, const nt2_la_int* ldvs, float* rconde, float* rcondv, nt2_la_complex* work,
                           const nt2_la_int* lwork, float* rwork, nt2_la_int* bwork, nt2_la_int* info);
  void NT2_F77NAME(sgeesx)(const char* jobvs, const char* sort, nt2::details::selectall2_t* selectall, const char* sense,
                           const nt2_la_int* n, float* a, const nt2_la_int* lda, nt2_la_int* sdim, float* wr, float* wi,
                           const float* vs, const nt2_la_int* ldvs, float* rconde, float* rcondv, float* work,
                           const nt2_la_int* lwork, nt2_la_int* iwork, const nt2_la_int* liwork, nt2_la_int* bwork, nt2_la_int* info);
  void NT2_F77NAME(zgeesx)(const char* jobvs, const char* sort, nt2::details::selectall_t* select, const char* sense,
                           const nt2_la_int* n, nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* sdim, nt2_la_complex* w,
                           const nt2_la_complex* vs, const nt2_la_int* ldvs, double* rconde, double* rcondv, nt2_la_complex* work,
                           const nt2_la_int* lwork, double* rwork, nt2_la_int* bwork, nt2_la_int* info);
  void NT2_F77NAME(dgeesx)(const char* jobvs, const char* sort, nt2::details::selectall2_t* select, const char* sense,
                           const nt2_la_int* n, double* a, const nt2_la_int* lda, nt2_la_int* sdim, double* wr, double* wi,
                           const double* vs, const nt2_la_int* ldvs, double* rconde, double* rcondv, double* work,
                           const nt2_la_int* lwork, nt2_la_int* iwork, const nt2_la_int* liwork, nt2_la_int* bwork, nt2_la_int* info);
}

//There is a bug in version 3.2.1 of lapapack
//bug0016 :: problem in workspace query for CGEESX/DGEESX/SGEESX/ZGEESX
// CORRECTED - see svn r657
// bug report sent by Alexander V. Kobotov (Intel) on Mon, 6 Apr 2009 to "lapack@cs.utk.edu".
//"(c/z)geesx: no lwork=-1 branch at all, info = -15 is returned while doing lquery."
//The S and D versions were not exiting after WORKSPACE query as well.
// committed by Julien Langou (SVN revision 657, on Sun May 10 2009)
//
// Also using the hint given in the doc of geesx is not sufficient for insuring
// a correct call yo gehrd.


#endif
