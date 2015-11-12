#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GGEV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GGEV_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? S or D
// \verbatim
// >
// > ?GGEV computes for a pair of N-by-N real nonsymmetric matrices (A,B)
// > the generalized eigenvalues, and optionally, the left and/or right
// > generalized eigenvectors.
// >
// > A generalized eigenvalue for a pair of matrices (A,B) is a scalar
// > lambda or a ratio alpha/beta = lambda, such that A - lambda*B is
// > singular. It is usually represented as the pair (alpha,beta), as
// > there is a reasonable interpretation for beta=0, and even for both
// > being zero.
// >
// > The right eigenvector v(j) corresponding to the eigenvalue lambda(j)
// > of (A,B) satisfies
// >
// > A * v(j) = lambda(j) * B * v(j).
// >
// > The left eigenvector u(j) corresponding to the eigenvalue lambda(j)
// > of (A,B) satisfies
// >
// > u(j)**H * A = lambda(j) * u(j)**H * B .
// >
// > where u(j)**H is the conjugate-transpose of u(j).
// >
// > \endverbatim

//  Arguments:
//  ==========

// > \param[in] JOBVL
// > \verbatim
// > JOBVL is CHARACTER*1
// > = 'N': do not compute the left generalized eigenvectors;
// > = 'V': compute the left generalized eigenvectors.
// > \endverbatim
// >
// > \param[in] JOBVR
// > \verbatim
// > JOBVR is CHARACTER*1
// > = 'N': do not compute the right generalized eigenvectors;
// > = 'V': compute the right generalized eigenvectors.
// > \endverbatim
// >
// > \param[in] N
// > \verbatim
// > N is INTEGER
// > The order of the matrices A, B, VL, and VR. N >= 0.
// > \endverbatim
// >
// > \param[in,out] A
// > \verbatim
// > A is REAL array, dimension (LDA, N)
// > On entry, the matrix A in the pair (A,B).
// > On exit, A has been overwritten.
// > \endverbatim
// >
// > \param[in] LDA
// > \verbatim
// > LDA is INTEGER
// > The leading dimension of A. LDA >= max(1,N).
// > \endverbatim
// >
// *> \param[in,out] B
// *> \verbatim
// *> B is REAL array, dimension (LDB, N)
// *> On entry, the matrix B in the pair (A,B).
// *> On exit, B has been overwritten.
// *> \endverbatim
// *>
// *> \param[in] LDB
// *> \verbatim
// *> LDB is INTEGER
// *> The leading dimension of B. LDB >= max(1,N).
// *> \endverbatim
// *>
// *> \param[out] ALPHAR
// *> \verbatim
// *> ALPHAR is REAL array, dimension (N)
// *> \endverbatim
// *>
// *> \param[out] ALPHAI
// *> \verbatim
// *> ALPHAI is REAL array, dimension (N)
// *> \endverbatim
// *>
// *> \param[out] BETA
// *> \verbatim
// *> BETA is REAL array, dimension (N)
// *> On exit, (ALPHAR(j) + ALPHAI(j)*i)/BETA(j), j=1,...,N, will
// *> be the generalized eigenvalues. If ALPHAI(j) is zero, then
// *> the j-th eigenvalue is real; if positive, then the j-th and
// *> (j+1)-st eigenvalues are a complex conjugate pair, with
// *> ALPHAI(j+1) negative.
// *>
// *> Note: the quotients ALPHAR(j)/BETA(j) and ALPHAI(j)/BETA(j)
// *> may easily over- or underflow, and BETA(j) may even be zero.
// *> Thus, the user should avoid naively computing the ratio
// *> alpha/beta. However, ALPHAR and ALPHAI will be always less
// *> than and usually comparable with norm(A) in magnitude, and
// *> BETA always less than and usually comparable with norm(B).
// *> \endverbatim
// *>
// *> \param[out] VL
// *> \verbatim
// *> VL is REAL array, dimension (LDVL,N)
// *> If JOBVL = 'V', the left eigenvectors u(j) are stored one
// *> after another in the columns of VL, in the same order as
// *> their eigenvalues. If the j-th eigenvalue is real, then
// *> u(j) = VL(:,j), the j-th column of VL. If the j-th and
// *> (j+1)-th eigenvalues form a complex conjugate pair, then
// *> u(j) = VL(:,j)+i*VL(:,j+1) and u(j+1) = VL(:,j)-i*VL(:,j+1).
// *> Each eigenvector is scaled so the largest component has
// *> abs(real part)+abs(imag. part)=1.
// *> Not referenced if JOBVL = 'N'.
// *> \endverbatim
// *>
// *> \param[in] LDVL
// *> \verbatim
// *> LDVL is INTEGER
// *> The leading dimension of the matrix VL. LDVL >= 1, and
// *> if JOBVL = 'V', LDVL >= N.
// *> \endverbatim
// *>
// *> \param[out] VR
// *> \verbatim
// *> VR is REAL array, dimension (LDVR,N)
// *> If JOBVR = 'V', the right eigenvectors v(j) are stored one
// *> after another in the columns of VR, in the same order as
// *> their eigenvalues. If the j-th eigenvalue is real, then
// *> v(j) = VR(:,j), the j-th column of VR. If the j-th and
// *> (j+1)-th eigenvalues form a complex conjugate pair, then
// *> v(j) = VR(:,j)+i*VR(:,j+1) and v(j+1) = VR(:,j)-i*VR(:,j+1).
// *> Each eigenvector is scaled so the largest component has
// *> abs(real part)+abs(imag. part)=1.
// *> Not referenced if JOBVR = 'N'.
// *> \endverbatim
// *>
// *> \param[in] LDVR
// *> \verbatim
// *> LDVR is INTEGER
// *> The leading dimension of the matrix VR. LDVR >= 1, and
// *> if JOBVR = 'V', LDVR >= N.
// *> \endverbatim
// *>
// *> \param[out] WORK
// *> \verbatim
// *> WORK is REAL array, dimension (MAX(1,LWORK))
// *> On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *> \endverbatim
// *>
// *> \param[in] LWORK
// *> \verbatim
// *> LWORK is INTEGER
// *> The dimension of the array WORK. LWORK >= max(1,8*N).
// *> For good performance, LWORK must generally be larger.
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
// *> = 1,...,N:
// *> The QZ iteration failed. No eigenvectors have been
// *> calculated, but ALPHAR(j), ALPHAI(j), and BETA(j)
// *> should be correct for j=INFO+1,...,N.
// *> > N: =N+1: other than QZ iteration failed in SHGEQZ.
// *> =N+2: error return from STGEVC.
// *> \endverbatim

extern "C"
{
  void NT2_F77NAME(zggev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* b, const nt2_la_int* ldb
                         , nt2_la_complex* alpha
                         , nt2_la_complex* beta
                         , const nt2_la_complex* vl, const nt2_la_int* ldvl
                         , const nt2_la_complex* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , nt2_la_complex* rwork
                         , nt2_la_int* info
                         );
  void NT2_F77NAME(cggev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* b, const nt2_la_int* ldb
                         , nt2_la_complex* alpha
                         , nt2_la_complex* beta
                         , const nt2_la_complex* vl, const nt2_la_int* ldvl
                         , const nt2_la_complex* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , nt2_la_complex* rwork
                         , nt2_la_int* info
                         );
  void NT2_F77NAME(dggev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* b, const nt2_la_int* ldb
                         , double* alphar,  double* alphai
                         , double* beta
                         , const double* vl, const nt2_la_int* ldvl
                         , const double* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , nt2_la_int* info
                         );
  void NT2_F77NAME(sggev)( const char* jobvl, const char* jobvr
                         , const nt2_la_int* n
                         , nt2_la_complex* a, const nt2_la_int* lda
                         , nt2_la_complex* b, const nt2_la_int* ldb
                         , float* alphar,  float* alphai
                         , float* beta
                         , const float* vl, const nt2_la_int* ldvl
                         , const float* vr, const nt2_la_int* ldvr
                         , nt2_la_complex* work
                         , const nt2_la_int* lwork
                         , nt2_la_int* info
                         );

}

#endif
