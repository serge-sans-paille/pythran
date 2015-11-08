//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEEV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEEV_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? C or Z
//       SUBROUTINE ?GEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
//      $                  LDVR, WORK, LWORK, INFO )
// * Definition:
// * ===========
// *
// * SUBROUTINE XGEEV( JOBVL, JOBVR, N, A, LDA, W, VL, LDVL, VR, LDVR,
// * WORK, LWORK, RWORK, INFO )
// *
// *> \par Purpose:
// * =============
// *>
// *> \verbatim
// *>
// *> ?GEEV computes for an N-by-N complex nonsymmetric matrix A, the
// *> eigenvalues and, optionally, the left and/or right eigenvectors.
// *>
// *> The right eigenvector v(j) of A satisfies
// *> A * v(j) = lambda(j) * v(j)
// *> where lambda(j) is its eigenvalue.
// *> The left eigenvector u(j) of A satisfies
// *> u(j)**H * A = lambda(j) * u(j)**H
// *> where u(j)**H denotes the conjugate transpose of u(j).
// *>
// *> The computed eigenvectors are normalized to have Euclidean norm
// *> equal to 1 and largest component real.
// *> \endverbatim
// *
// * Arguments:
// * ==========
// *
// *> \param[in] JOBVL
// *> \verbatim
// *> JOBVL is CHARACTER*1
// *> = 'N': left eigenvectors of A are not computed;
// *> = 'V': left eigenvectors of are computed.
// *> \endverbatim
// *>
// *> \param[in] JOBVR
// *> \verbatim
// *> JOBVR is CHARACTER*1
// *> = 'N': right eigenvectors of A are not computed;
// *> = 'V': right eigenvectors of A are computed.
// *> \endverbatim
// *>
// *> \param[in] N
// *> \verbatim
// *> N is INTEGER
// *> The order of the matrix A. N >= 0.
// *> \endverbatim
// *>
// *> \param[in,out] A
// *> \verbatim
// *> A is COMPLEX array, dimension (LDA,N)
// *> On entry, the N-by-N matrix A.
// *> On exit, A has been overwritten.
// *> \endverbatim
// *>
// *> \param[in] LDA
// *> \verbatim
// *> LDA is INTEGER
// *> The leading dimension of the array A. LDA >= max(1,N).
// *> \endverbatim
// *>
// *> \param[out] W
// *> \verbatim
// *> W is COMPLEX/REAL array, dimension (N)
// *> W contains the computed eigenvalues.
// *> \endverbatim
// *>
// *> \param[out] VL
// *> \verbatim
// *> VL is COMPLEX array, dimension (LDVL,N)
// *> If JOBVL = 'V', the left eigenvectors u(j) are stored one
// *> after another in the columns of VL, in the same order
// *> as their eigenvalues.
// *> If JOBVL = 'N', VL is not referenced.
// *> u(j) = VL(:,j), the j-th column of VL.
// *> \endverbatim
// *>
// *> \param[in] LDVL
// *> \verbatim
// *> LDVL is INTEGER
// *> The leading dimension of the array VL. LDVL >= 1; if
// *> JOBVL = 'V', LDVL >= N.
// *> \endverbatim
// *>
// *> \param[out] VR
// *> \verbatim
// *> VR is COMPLEX array, dimension (LDVR,N)
// *> If JOBVR = 'V', the right eigenvectors v(j) are stored one
// *> after another in the columns of VR, in the same order
// *> as their eigenvalues.
// *> If JOBVR = 'N', VR is not referenced.
// *> v(j) = VR(:,j), the j-th column of VR.
// *> \endverbatim
// *>
// *> \param[in] LDVR
// *> \verbatim
// *> LDVR is INTEGER
// *> The leading dimension of the array VR. LDVR >= 1; if
// *> JOBVR = 'V', LDVR >= N.
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
// *> The dimension of the array WORK. LWORK >= max(1,2*N).
// *> For good performance, LWORK must generally be larger.
// *>
// *> If LWORK = -1, then a workspace query is assumed; the routine
// *> only calculates the optimal size of the WORK array, returns
// *> this value as the first entry of the WORK array, and no error
// *> message related to LWORK is issued by XERBLA.
// *> \endverbatim
// *>
// *> \param[out] RWORK
// *> \verbatim
// *> RWORK is REAL array, dimension (2*N)
// *> \endverbatim
// *>
// *> \param[out] INFO
// *> \verbatim
// *> INFO is INTEGER
// *> = 0: successful exit
// *> < 0: if INFO = -i, the i-th argument had an illegal value.
// *> > 0: if INFO = i, the QR algorithm failed to compute all the
// *> eigenvalues, and no eigenvectors have been computed;
// *> elements and i+1:N of W contain eigenvalues which have
// *> converged.
// *> \endverbatim
// *
// *
///////////////////////////////////////////////////////////////////////
/// FOR ? S or D
// * SUBROUTINE ?GEEV( JOBVL, JOBVR, N, A, LDA, WR, WI, VL, LDVL, VR,
// * LDVR, WORK, LWORK, INFO )
// *
// *> \par Purpose:
// * =============
// *>
// *> \verbatim
// *>
// *> ?GEEV computes for an N-by-N real nonsymmetric matrix A, the
// *> eigenvalues and, optionally, the left and/or right eigenvectors.
// *>
// *> The right eigenvector v(j) of A satisfies
// *> A * v(j) = lambda(j) * v(j)
// *> where lambda(j) is its eigenvalue.
// *> The left eigenvector u(j) of A satisfies
// *> u(j)**H * A = lambda(j) * u(j)**H
// *> where u(j)**H denotes the conjugate-transpose of u(j).
// *>
// *> The computed eigenvectors are normalized to have Euclidean norm
// *> equal to 1 and largest component real.
// *> \endverbatim
// *
// * Arguments:
// * ==========
// *
// *> \param[in] JOBVL
// *> \verbatim
// *> JOBVL is CHARACTER*1
// *> = 'N': left eigenvectors of A are not computed;
// *> = 'V': left eigenvectors of A are computed.
// *> \endverbatim
// *>
// *> \param[in] JOBVR
// *> \verbatim
// *> JOBVR is CHARACTER*1
// *> = 'N': right eigenvectors of A are not computed;
// *> = 'V': right eigenvectors of A are computed.
// *> \endverbatim
// *>
// *> \param[in] N
// *> \verbatim
// *> N is INTEGER
// *> The order of the matrix A. N >= 0.
// *> \endverbatim
// *>
// *> \param[in,out] A
// *> \verbatim
// *> A is DOUBLE PRECISION array, dimension (LDA,N)
// *> On entry, the N-by-N matrix A.
// *> On exit, A has been overwritten.
// *> \endverbatim
// *>
// *> \param[in] LDA
// *> \verbatim
// *> LDA is INTEGER
// *> The leading dimension of the array A. LDA >= max(1,N).
// *> \endverbatim
// *>
// *> \param[out] WR
// *> \verbatim
// *> WR is DOUBLE PRECISION array, dimension (N)
// *> \endverbatim
// *>
// *> \param[out] WI
// *> \verbatim
// *> WI is DOUBLE PRECISION array, dimension (N)
// *> WR and WI contain the real and imaginary parts,
// *> respectively, of the computed eigenvalues. Complex
// *> conjugate pairs of eigenvalues appear consecutively
// *> with the eigenvalue having the positive imaginary part
// *> first.
// *> \endverbatim
// *>
// *> \param[out] VL
// *> \verbatim
// *> VL is DOUBLE PRECISION array, dimension (LDVL,N)
// *> If JOBVL = 'V', the left eigenvectors u(j) are stored one
// *> after another in the columns of VL, in the same order
// *> as their eigenvalues.
// *> If JOBVL = 'N', VL is not referenced.
// *> If the j-th eigenvalue is real, then u(j) = VL(:,j),
// *> the j-th column of VL.
// *> If the j-th and (j+1)-st eigenvalues form a complex
// *> conjugate pair, then u(j) = VL(:,j) + i*VL(:,j+1) and
// *> u(j+1) = VL(:,j) - i*VL(:,j+1).
// *> \endverbatim
// *>
// *> \param[in] LDVL
// *> \verbatim
// *> LDVL is INTEGER
// *> The leading dimension of the array VL. LDVL >= 1; if
// *> JOBVL = 'V', LDVL >= N.
// *> \endverbatim
// *>
// *> \param[out] VR
// *> \verbatim
// *> VR is DOUBLE PRECISION array, dimension (LDVR,N)
// *> If JOBVR = 'V', the right eigenvectors v(j) are stored one
// *> after another in the columns of VR, in the same order
// *> as their eigenvalues.
// *> If JOBVR = 'N', VR is not referenced.
// *> If the j-th eigenvalue is real, then v(j) = VR(:,j),
// *> the j-th column of VR.
// *> If the j-th and (j+1)-st eigenvalues form a complex
// *> conjugate pair, then v(j) = VR(:,j) + i*VR(:,j+1) and
// *> v(j+1) = VR(:,j) - i*VR(:,j+1).
// *> \endverbatim
// *>
// *> \param[in] LDVR
// *> \verbatim
// *> LDVR is INTEGER
// *> The leading dimension of the array VR. LDVR >= 1; if
// *> JOBVR = 'V', LDVR >= N.
// *> \endverbatim
// *>
// *> \param[out] WORK
// *> \verbatim
// *> WORK is DOUBLE PRECISION array, dimension (MAX(1,LWORK))
// *> On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *> \endverbatim
// *>
// *> \param[in] LWORK
// *> \verbatim
// *> LWORK is INTEGER
// *> The dimension of the array WORK. LWORK >= max(1,3*N), and
// *> if JOBVL = 'V' or JOBVR = 'V', LWORK >= 4*N. For good
// *> performance, LWORK must generally be larger.
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
// *> = 0: successful exit
// *> < 0: if INFO = -i, the i-th argument had an illegal value.
// *> > 0: if INFO = i, the QR algorithm failed to compute all the
// *> eigenvalues, and no eigenvectors have been computed;
// *> elements i+1:N of WR and WI contain eigenvalues which
// *> have converged.
// *> \endverbatim

extern "C"
{

  void NT2_F77NAME(cgeev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* w
                         , const nt2_la_complex* vl, const nt2_la_int* ldvl
                         , const nt2_la_complex* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , float* rwork
                         , nt2_la_int* info
                         );

  void NT2_F77NAME(zgeev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* w
                         , const nt2_la_complex* vl, const nt2_la_int* ldvl
                         , const nt2_la_complex* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , double* rwork
                         , nt2_la_int* info
                         );

  void NT2_F77NAME(sgeev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , float* a, const nt2_la_int* lda
                         , float* wr, nt2_la_complex* wi
                         , const float* vl, const nt2_la_int* ldvl
                         , const float* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , nt2_la_int* info
                         );

  void NT2_F77NAME(dgeev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , double* a, const nt2_la_int* lda
                         , double* wr, nt2_la_complex* wi
                         , const double* vl, const nt2_la_int* ldvl
                         , const double* vr, const nt2_la_int* ldvr
                         , double* work
                         , const nt2_la_int* lwork
                         , nt2_la_int* info
                         );
}

#endif
