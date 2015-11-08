//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GESVD_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GESVD_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>


/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
// * FOR ? =  C or Z
// * Definition:
// * ===========
// *
// * SUBROUTINE CGESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT,
// * WORK, LWORK, RWORK, INFO )
// *
// *> \par Purpose:
// * =============
// *>
// *> \verbatim
// *>
// *> CGESVD computes the singular value decomposition (SVD) of a complex
// *> M-by-N matrix A, optionally computing the left and/or right singular
// *> vectors. The SVD is written
// *>
// *> A = U * SIGMA * conjugate-transpose(V)
// *>
// *> where SIGMA is an M-by-N matrix which is zero except for its
// *> min(m,n) diagonal elements, U is an M-by-M unitary matrix, and
// *> V is an N-by-N unitary matrix. The diagonal elements of SIGMA
// *> are the singular values of A; they are real and non-negative, and
// *> are returned in descending order. The first min(m,n) columns of
// *> U and V are the left and right singular vectors of A.
// *>
// *> Note that the routine returns V**H, not V.
// *> \endverbatim
// *
// * Arguments:
// * ==========
// *
// *> \param[in] JOBU
// *> \verbatim
// *> JOBU is CHARACTER*1
// *> Specifies options for computing all or part of the matrix U:
// *> = 'A': all M columns of U are returned in array U:
// *> = 'S': the first min(m,n) columns of U (the left singular
// *> vectors) are returned in the array U;
// *> = 'O': the first min(m,n) columns of U (the left singular
// *> vectors) are overwritten on the array A;
// *> = 'N': no columns of U (no left singular vectors) are
// *> computed.
// *> \endverbatim
// *>
// *> \param[in] JOBVT
// *> \verbatim
// *> JOBVT is CHARACTER*1
// *> Specifies options for computing all or part of the matrix
// *> V**H:
// *> = 'A': all N rows of V**H are returned in the array VT;
// *> = 'S': the first min(m,n) rows of V**H (the right singular
// *> vectors) are returned in the array VT;
// *> = 'O': the first min(m,n) rows of V**H (the right singular
// *> vectors) are overwritten on the array A;
// *> = 'N': no rows of V**H (no right singular vectors) are
// *> computed.
// *>
// *> JOBVT and JOBU cannot both be 'O'.
// *> \endverbatim
// *>
// *> \param[in] M
// *> \verbatim
// *> M is INTEGER
// *> The number of rows of the input matrix A. M >= 0.
// *> \endverbatim
// *>
// *> \param[in] N
// *> \verbatim
// *> N is INTEGER
// *> The number of columns of the input matrix A. N >= 0.
// *> \endverbatim
// *>
// *> \param[in,out] A
// *> \verbatim
// *> A is COMPLEX array, dimension (LDA,N)
// *> On entry, the M-by-N matrix A.
// *> On exit,
// *> if JOBU = 'O', A is overwritten with the first min(m,n)
// *> columns of U (the left singular vectors,
// *> stored columnwise);
// *> if JOBVT = 'O', A is overwritten with the first min(m,n)
// *> rows of V**H (the right singular vectors,
// *> stored rowwise);
// *> if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A
// *> are destroyed.
// *> \endverbatim
// *>
// *> \param[in] LDA
// *> \verbatim
// *> LDA is INTEGER
// *> The leading dimension of the array A. LDA >= max(1,M).
// *> \endverbatim
// *>
// *> \param[out] S
// *> \verbatim
// *> S is REAL array, dimension (min(M,N))
// *> The singular values of A, sorted so that S(i) >= S(i+1).
// *> \endverbatim
// *>
// *> \param[out] U
// *> \verbatim
// *> U is COMPLEX array, dimension (LDU,UCOL)
// *> (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'.
// *> If JOBU = 'A', U contains the M-by-M unitary matrix U;
// *> if JOBU = 'S', U contains the first min(m,n) columns of U
// *> (the left singular vectors, stored columnwise);
// *> if JOBU = 'N' or 'O', U is not referenced.
// *> \endverbatim
// *>
// *> \param[in] LDU
// *> \verbatim
// *> LDU is INTEGER
// *> The leading dimension of the array U. LDU >= 1; if
// *> JOBU = 'S' or 'A', LDU >= M.
// *> \endverbatim
// *>
// *> \param[out] VT
// *> \verbatim
// *> VT is COMPLEX array, dimension (LDVT,N)
// *> If JOBVT = 'A', VT contains the N-by-N unitary matrix
// *> V**H;
// *> if JOBVT = 'S', VT contains the first min(m,n) rows of
// *> V**H (the right singular vectors, stored rowwise);
// *> if JOBVT = 'N' or 'O', VT is not referenced.
// *> \endverbatim
// *>
// *> \param[in] LDVT
// *> \verbatim
// *> LDVT is INTEGER
// *> The leading dimension of the array VT. LDVT >= 1; if
// *> JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N).
// *> \endverbatim
// *>
// *> \param[out] WORK
// *> \verbatim
// *> WORK is COMPLEX array, dimension (MAX(1,LWORK))
// *> On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *> \endverbatim
// *>
// *> \param[in] LWORK
// *> \verbatim
// *> LWORK is INTEGER
// *> The dimension of the array WORK.
// *> LWORK >= MAX(1,2*MIN(M,N)+MAX(M,N)).
// *> For good performance, LWORK should generally be larger.
// *>
// *> If LWORK = -1, then a workspace query is assumed; the routine
// *> only calculates the optimal size of the WORK array, returns
// *> this value as the first entry of the WORK array, and no error
// *> message related to LWORK is issued by XERBLA.
// *> \endverbatim
// *>
// *> \param[out] RWORK
// *> \verbatim
// *> RWORK is REAL array, dimension (5*min(M,N))
// *> On exit, if INFO > 0, RWORK(1:MIN(M,N)-1) contains the
// *> unconverged superdiagonal elements of an upper bidiagonal
// *> matrix B whose diagonal is in S (not necessarily sorted).
// *> B satisfies A = U * B * VT, so it has the same singular
// *> values as A, and singular vectors related by U and VT.
// *> \endverbatim
// *>
// *> \param[out] INFO
// *> \verbatim
// *> INFO is INTEGER
// *> = 0: successful exit.
// *> < 0: if INFO = -i, the i-th argument had an illegal value.
// *> > 0: if CBDSQR did not converge, INFO specifies how many
// *> superdiagonals of an intermediate bidiagonal form B
// *> did not converge to zero. See the description of RWORK
// *> above for details.
// *> \endverbatim
// *
////////////////////////////////////////////////////////////////////////
// For ? =  S or D
// * Definition:
// * ===========
// *
// * SUBROUTINE ?GESVD( JOBU, JOBVT, M, N, A, LDA, S, U, LDU, VT, LDVT,
// * WORK, LWORK, INFO )
// *
// *> \par Purpose:
// * =============
// *>
// *> \verbatim
// *>
// *> ?GESVD computes the singular value decomposition (SVD) of a real
// *> M-by-N matrix A, optionally computing the left and/or right singular
// *> vectors. The SVD is written
// *>
// *> A = U * SIGMA * transpose(V)
// *>
// *> where SIGMA is an M-by-N matrix which is zero except for its
// *> min(m,n) diagonal elements, U is an M-by-M orthogonal matrix, and
// *> V is an N-by-N orthogonal matrix. The diagonal elements of SIGMA
// *> are the singular values of A; they are real and non-negative, and
// *> are returned in descending order. The first min(m,n) columns of
// *> U and V are the left and right singular vectors of A.
// *>
// *> Note that the routine returns V**T, not V.
// *> \endverbatim
// *
// * Arguments:
// * ==========
// *
// *> \param[in] JOBU
// *> \verbatim
// *> JOBU is CHARACTER*1
// *> Specifies options for computing all or part of the matrix U:
// *> = 'A': all M columns of U are returned in array U:
// *> = 'S': the first min(m,n) columns of U (the left singular
// *> vectors) are returned in the array U;
// *> = 'O': the first min(m,n) columns of U (the left singular
// *> vectors) are overwritten on the array A;
// *> = 'N': no columns of U (no left singular vectors) are
// *> computed.
// *> \endverbatim
// *>
// *> \param[in] JOBVT
// *> \verbatim
// *> JOBVT is CHARACTER*1
// *> Specifies options for computing all or part of the matrix
// *> V**T:
// *> = 'A': all N rows of V**T are returned in the array VT;
// *> = 'S': the first min(m,n) rows of V**T (the right singular
// *> vectors) are returned in the array VT;
// *> = 'O': the first min(m,n) rows of V**T (the right singular
// *> vectors) are overwritten on the array A;
// *> = 'N': no rows of V**T (no right singular vectors) are
// *> computed.
// *>
// *> JOBVT and JOBU cannot both be 'O'.
// *> \endverbatim
// *>
// *> \param[in] M
// *> \verbatim
// *> M is INTEGER
// *> The number of rows of the input matrix A. M >= 0.
// *> \endverbatim
// *>
// *> \param[in] N
// *> \verbatim
// *> N is INTEGER
// *> The number of columns of the input matrix A. N >= 0.
// *> \endverbatim
// *>
// *> \param[in,out] A
// *> \verbatim
// *> A is DOUBLE PRECISION array, dimension (LDA,N)
// *> On entry, the M-by-N matrix A.
// *> On exit,
// *> if JOBU = 'O', A is overwritten with the first min(m,n)
// *> columns of U (the left singular vectors,
// *> stored columnwise);
// *> if JOBVT = 'O', A is overwritten with the first min(m,n)
// *> rows of V**T (the right singular vectors,
// *> stored rowwise);
// *> if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A
// *> are destroyed.
// *> \endverbatim
// *>
// *> \param[in] LDA
// *> \verbatim
// *> LDA is INTEGER
// *> The leading dimension of the array A. LDA >= max(1,M).
// *> \endverbatim
// *>
// *> \param[out] S
// *> \verbatim
// *> S is DOUBLE PRECISION array, dimension (min(M,N))
// *> The singular values of A, sorted so that S(i) >= S(i+1).
// *> \endverbatim
// *>
// *> \param[out] U
// *> \verbatim
// *> U is DOUBLE PRECISION array, dimension (LDU,UCOL)
// *> (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'.
// *> If JOBU = 'A', U contains the M-by-M orthogonal matrix U;
// *> if JOBU = 'S', U contains the first min(m,n) columns of U
// *> (the left singular vectors, stored columnwise);
// *> if JOBU = 'N' or 'O', U is not referenced.
// *> \endverbatim
// *>
// *> \param[in] LDU
// *> \verbatim
// *> LDU is INTEGER
// *> The leading dimension of the array U. LDU >= 1; if
// *> JOBU = 'S' or 'A', LDU >= M.
// *> \endverbatim
// *>
// *> \param[out] VT
// *> \verbatim
// *> VT is DOUBLE PRECISION array, dimension (LDVT,N)
// *> If JOBVT = 'A', VT contains the N-by-N orthogonal matrix
// *> V**T;
// *> if JOBVT = 'S', VT contains the first min(m,n) rows of
// *> V**T (the right singular vectors, stored rowwise);
// *> if JOBVT = 'N' or 'O', VT is not referenced.
// *> \endverbatim
// *>
// *> \param[in] LDVT
// *> \verbatim
// *> LDVT is INTEGER
// *> The leading dimension of the array VT. LDVT >= 1; if
// *> JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N).
// *> \endverbatim
// *>
// *> \param[out] WORK
// *> \verbatim
// *> WORK is DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// *> On exit, if INFO = 0, WORK(1) returns the optimal LWORK;
// *> if INFO > 0, WORK(2:MIN(M,N)) contains the unconverged
// *> superdiagonal elements of an upper bidiagonal matrix B
// *> whose diagonal is in S (not necessarily sorted). B
// *> satisfies A = U * B * VT, so it has the same singular values
// *> as A, and singular vectors related by U and VT.
// *> \endverbatim
// *>
// *> \param[in] LWORK
// *> \verbatim
// *> LWORK is INTEGER
// *> The dimension of the array WORK.
// *> LWORK >= MAX(1,5*MIN(M,N)) for the paths (see comments inside code):
// *> - PATH 1 (M much larger than N, JOBU='N')
// *> - PATH 1t (N much larger than M, JOBVT='N')
// *> LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N)) for the other paths
// *> For good performance, LWORK should generally be larger.
// *>
// *> If LWORK = -1, then a workspace query is assumed; the routine
// *> only calculates the optimal size of the WORK array, returns
// *> this value as the first entry of the WORK array, and no error
// *> message related to LWORK is issued by XERBLA.
// *> \endverbatim
// *>
// *> \param[out] INFO
// *> \verbatim
// *> INFO is INTEGER
// *> = 0: successful exit.
// *> < 0: if INFO = -i, the i-th argument had an illegal value.
// *> > 0: if DBDSQR did not converge, INFO specifies how many
// *> superdiagonals of an intermediate bidiagonal form B
// *> did not converge to zero. See the description of WORK
// *> above for details.
// *> \endverbatim
// *

extern "C"
{
  void NT2_F77NAME(dgesvd)( const char* jobu       , const char* jobvt
                          , const nt2_la_int* m    , const nt2_la_int* n
                          , double* a        , const nt2_la_int* lda
                          , double* s              , double* u
                          , const nt2_la_int* ldu  , double* vt
                          , const nt2_la_int* ldvt , double* work
                          , const nt2_la_int* lwork, nt2_la_int* info
                          );

  void NT2_F77NAME(sgesvd)( const char* jobu       , const char* jobvt
                          , const nt2_la_int* m    , const nt2_la_int* n
                          , float* a               , const nt2_la_int* lda
                          , float* s               , float* u
                          , const nt2_la_int* ldu  , float* vt
                          , const nt2_la_int* ldvt , float* work
                          , const nt2_la_int* lwork, nt2_la_int* info
                          );

  void NT2_F77NAME(cgesvd)( const char* jobu       , const char* jobvt
                          , const nt2_la_int* m    , const nt2_la_int* n
                          , nt2_la_complex* a      , const nt2_la_int* lda
                          , float* s               , nt2_la_complex* u
                          , const nt2_la_int* ldu  , nt2_la_complex* vt
                          , const nt2_la_int* ldvt , nt2_la_complex* work
                          , const nt2_la_int* lwork, float* rwork
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zgesvd)( const char* jobu       , const char* jobvt
                          , const nt2_la_int* m    , const nt2_la_int* n
                          , nt2_la_complex* a      , const nt2_la_int* lda
                          , double* s              , nt2_la_complex* u
                          , const nt2_la_int* ldu  , nt2_la_complex* vt
                          , const nt2_la_int* ldvt , nt2_la_complex* work
                          , const nt2_la_int* lwork, double* rwork
                          , nt2_la_int* info
                          );
}

#endif
