//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GEEVX_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GEEVX_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
// *  CGEEVX computes for an N-by-N complex nonsymmetric matrix A, the
// *  eigenvalues and, optionally, the left and/or right eigenvectors.
// *
// *  Optionally also, it computes a balancing transformation to improve
// *  the conditioning of the eigenvalues and eigenvectors (ILO, IHI,
// *  SCALE, and ABNRM), reciprocal condition numbers for the eigenvalues
// *  (RCONDE), and reciprocal condition numbers for the right
// *  eigenvectors (RCONDV).
// *
// *  The right eigenvector v(j) of A satisfies
// *                   A * v(j) = lambda(j) * v(j)
// *  where lambda(j) is its eigenvalue.
// *  The left eigenvector u(j) of A satisfies
// *                u(j)**H * A = lambda(j) * u(j)**H
// *  where u(j)**H denotes the conjugate transpose of u(j).
// *
// *  The computed eigenvectors are normalized to have Euclidean norm
// *  equal to 1 and largest component real.
// *
// *  Balancing a matrix means permuting the rows and columns to make it
// *  more nearly upper triangular, and applying a diagonal similarity
// *  transformation D * A * D**(-1), where D is a diagonal matrix, to
// *  make its rows and columns closer in norm and the condition numbers
// *  of its eigenvalues and eigenvectors smaller.  The computed
// *  reciprocal condition numbers correspond to the balanced matrix.
// *  Permuting rows and columns will not change the condition numbers
// *  (in exact arithmetic) but diagonal scaling will.  For further
// *  explanation of balancing, see section 4.10.2 of the LAPACK
// *  Users' Guide.
// *
// *  Arguments
// *  =========
// *
// *  BALANC  (input) CHARACTER*1
// *          Indicates how the input matrix should be diagonally scaled
// *          and/or permuted to improve the conditioning of its
// *          eigenvalues.
// *          = 'N': Do not diagonally scale or permute;
// *          = 'P': Perform permutations to make the matrix more nearly
// *                 upper triangular. Do not diagonally scale;
// *          = 'S': Diagonally scale the matrix, ie. replace A by
// *                 D*A*D**(-1), where D is a diagonal matrix chosen
// *                 to make the rows and columns of A more equal in
// *                 norm. Do not permute;
// *          = 'B': Both diagonally scale and permute A.
// *
// *          Computed reciprocal condition numbers will be for the matrix
// *          after balancing and/or permuting. Permuting does not change
// *          condition numbers (in exact arithmetic), but balancing does.
// *
// *  JOBVL   (input) CHARACTER*1
// *          = 'N': left eigenvectors of A are not computed;
// *          = 'V': left eigenvectors of A are computed.
// *          If SENSE = 'E' or 'B', JOBVL must = 'V'.
// *
// *  JOBVR   (input) CHARACTER*1
// *          = 'N': right eigenvectors of A are not computed;
// *          = 'V': right eigenvectors of A are computed.
// *          If SENSE = 'E' or 'B', JOBVR must = 'V'.
// *
// *  SENSE   (input) CHARACTER*1
// *          Determines which reciprocal condition numbers are computed.
// *          = 'N': None are computed;
// *          = 'E': Computed for eigenvalues only;
// *          = 'V': Computed for right eigenvectors only;
// *          = 'B': Computed for eigenvalues and right eigenvectors.
// *
// *          If SENSE = 'E' or 'B', both left and right eigenvectors
// *          must also be computed (JOBVL = 'V' and JOBVR = 'V').
// *
// *  N       (input) INTEGER
// *          The order of the matrix A. N >= 0.
// *
// *  A       (input/output) COMPLEX array, dimension (LDA,N)
// *          On entry, the N-by-N matrix A.
// *          On exit, A has been overwritten.  If JOBVL = 'V' or
// *          JOBVR = 'V', A contains the Schur form of the balanced
// *          version of the matrix A.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,N).
// *
// *  W       (output) COMPLEX array, dimension (N)
// *          W contains the computed eigenvalues.
// *
// *  VL      (output) COMPLEX array, dimension (LDVL,N)
// *          If JOBVL = 'V', the left eigenvectors u(j) are stored one
// *          after another in the columns of VL, in the same order
// *          as their eigenvalues.
// *          If JOBVL = 'N', VL is not referenced.
// *          u(j) = VL(:,j), the j-th column of VL.
// *
// *  LDVL    (input) INTEGER
// *          The leading dimension of the array VL.  LDVL >= 1; if
// *          JOBVL = 'V', LDVL >= N.
// *
// *  VR      (output) COMPLEX array, dimension (LDVR,N)
// *          If JOBVR = 'V', the right eigenvectors v(j) are stored one
// *          after another in the columns of VR, in the same order
// *          as their eigenvalues.
// *          If JOBVR = 'N', VR is not referenced.
// *          v(j) = VR(:,j), the j-th column of VR.
// *
// *  LDVR    (input) INTEGER
// *          The leading dimension of the array VR.  LDVR >= 1; if
// *          JOBVR = 'V', LDVR >= N.
// *
// *  ILO     (output) INTEGER
// *  IHI     (output) INTEGER
// *          ILO and IHI are integer values determined when A was
// *          balanced.  The balanced A(i,j) = 0 if I > J and
// *          J = 1,...,ILO-1 or I = IHI+1,...,N.
// *
// *  SCALE   (output) REAL array, dimension (N)
// *          Details of the permutations and scaling factors applied
// *          when balancing A.  If P(j) is the index of the row and column
// *          interchanged with row and column j, and D(j) is the scaling
// *          factor applied to row and column j, then
// *          SCALE(J) = P(J),    for J = 1,...,ILO-1
// *                   = D(J),    for J = ILO,...,IHI
// *                   = P(J)     for J = IHI+1,...,N.
// *          The order in which the interchanges are made is N to IHI+1,
// *          then 1 to ILO-1.
// *
// *  ABNRM   (output) REAL
// *          The one-norm of the balanced matrix (the maximum
// *          of the sum of absolute values of elements of any column).
// *
// *  RCONDE  (output) REAL array, dimension (N)
// *          RCONDE(j) is the reciprocal condition number of the j-th
// *          eigenvalue.
// *
// *  RCONDV  (output) REAL array, dimension (N)
// *          RCONDV(j) is the reciprocal condition number of the j-th
// *          right eigenvector.
// *
// *  WORK    (workspace/output) COMPLEX array, dimension (MAX(1,LWORK))
// *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// *
// *  LWORK   (input) INTEGER
// *          The dimension of the array WORK.  If SENSE = 'N' or 'E',
// *          LWORK >= max(1,2*N), and if SENSE = 'V' or 'B',
// *          LWORK >= N*N+2*N.
// *          For good performance, LWORK must generally be larger.
// *
// *          If LWORK = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the WORK array, returns
// *          this value as the first entry of the WORK array, and no error
// *          message related to LWORK is issued by XERBLA.
// *
// *  RWORK   (workspace) REAL array, dimension (2*N)
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value.
// *          > 0:  if INFO = i, the QR algorithm failed to compute all the
// *                eigenvalues, and no eigenvectors or condition numbers
// *                have been computed; elements 1:ILO-1 and i+1:N of W
// *                contain eigenvalues which have converged.
// *

namespace nt2
{
  namespace details
  {
    //////////////////////////////////////////////////////////////////////
    // geevx calls
    //////////////////////////////////////////////////////////////////////

    extern "C"
    {
      void NT2_F77NAME(cgeevx)(const char* balanc, const char* jobvl, const char* jobvr,
                               const char* sense, const nt2_la_int* n, const
                               nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* w,
                               const nt2_la_complex* vl, const nt2_la_int* ldvl,
                               const nt2_la_complex* vr, const nt2_la_int* ldvr, nt2_la_int* ilo, nt2_la_int* ihi,
                               float* scale, float* abnrm, float* rconde, float* rcondv,
                               nt2_la_complex* work, const nt2_la_int* lwork, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgeevx)(const char* balanc, const char* jobvl, const char* jobvr,
                               const char* sense, const nt2_la_int* n,
                               const double* a, const nt2_la_int* lda, double* wr, double* wi,
                               const double* vl, const nt2_la_int* ldvl,
                               const double* vr, const nt2_la_int* ldvr, nt2_la_int* ilo, nt2_la_int* ihi,
                               double* scale, double* abnrm, double* rconde, double* rcondv,
                               double* work, const nt2_la_int* lwork, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(sgeevx)(const char* balanc, const char* jobvl, const char* jobvr,
                               const char* sense, const nt2_la_int* n,
                               const float* a, const nt2_la_int* lda, float* wr, float* wi,
                               const float* vl, const nt2_la_int* ldvl,
                               const float* vr, const nt2_la_int* ldvr,
                               nt2_la_int* ilo, nt2_la_int* ihi, float* scale, float* abnrm,
                               float* rconde, float* rcondv,
                               float* work, const nt2_la_int* lwork, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(zgeevx)(const char* balanc, const char* jobvl, const char* jobvr,
                               const char* sense, const nt2_la_int* n,
                               const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* w,
                               const nt2_la_complex* vl, const nt2_la_int* ldvl,
                               const nt2_la_complex* vr, const nt2_la_int* ldvr,
                               nt2_la_int* ilo, nt2_la_int* ihi, double* scale, double* abnrm,
                               double* rconde, double* rcondv,
                               nt2_la_complex* work, const nt2_la_int* lwork, double* rwork, nt2_la_int* info);
    }

#define NT2_GEEVX(NAME, T)                                      \
    inline void geevx(const char* balanc,                       \
                      const char* jobvl,                        \
                      const char* jobvr,                        \
                      const char* sense,                        \
                      const nt2_la_int* n,                      \
                      const T* a,                               \
                      const nt2_la_int* lda,                    \
                      T* wr,                                    \
                      T* wi,                                    \
                      const T* vl,                              \
                      const nt2_la_int* ldvl,                   \
                      const T* vr,                              \
                      const nt2_la_int* ldvr,                   \
                      nt2_la_int* ilo,                          \
                      nt2_la_int* ihi,                          \
                      T* scale,                                 \
                      T* abnrm,                                 \
                      T* rconde,                                \
                      T* rcondv,                                \
                      nt2_la_int* info,                         \
                      nt2::details::workspace<T> & w)           \
    {                                                           \
      w.resizeiw((*sense == 'N' ||                              \
                  *sense) ==  'E')                              \
                 ? 1                                            \
                 : 2**n-2                                       \
                 );                                             \
      NT2_F77NAME( NAME )(balanc, jobvl, jobvr, sense,          \
                          n, a, lda, wr, wi, vl, ldvl,          \
                          vr, ldvr, ilo, ihi, scale,            \
                          abnrm, rconde, rcondv, w.main(),      \
                          query(), w.integers(), info);         \
        nt2_la_int wn = w.main_need();                          \
        w.resize_main(wn);                                      \
      NT2_F77NAME( NAME )(balanc, jobvl, jobvr, sense,          \
                          n, a, lda, wr, wi, vl, ldvl,          \
                          vr, ldvr, ilo, ihi, scale,            \
                          abnrm, rconde, rcondv, w.main(),      \
                          &wn(), w.integers(),                  \
                          info);                                \
    }                                                           \
    inline void geevx(const char* balanc,                       \
                      const char* jobvl,                        \
                      const char* jobvr,                        \
                      const char* sense,                        \
                      const nt2_la_int* n,                      \
                      const T* a,                               \
                      const nt2_la_int* lda,                    \
                      T* wr,                                    \
                      T* wi,                                    \
                      const T* vl,                              \
                      const nt2_la_int* ldvl,                   \
                      const T* vr,                              \
                      const nt2_la_int* ldvr,                   \
                      nt2_la_int* ilo,                          \
                      nt2_la_int* ihi,                          \
                      T* scale,                                 \
                      T* abnrm,                                 \
                      T* rconde,                                \
                      T* rcondv,                                \
                      nt2_la_int* info)                         \
    {                                                           \
      nt2::details::workspace<T> w;                             \
      geevx(balanc, jobvl, jobvr, sense,                        \
            n, a, lda, wr, wi, vl, ldvl,                        \
            vr, ldvr, ilo, ihi, scale,                          \
            abnrm, rconde, rcondv,                              \
            info, w);                                           \
    }                                                           \
      /**/
    NT2_GEEVX(sgeevx, float)
    NT2_GEEVX(dgeevx, double)

#undef NT2_GEEVX

#define NT2_GEEVX(NAME, T, TBASE)                               \
      inline void geevx(const char* balanc,                     \
                        const char* jobvl,                      \
                        const char* jobvr,                      \
                        const char* sense,                      \
                        const nt2_la_int* n,                    \
                        const T* a,                             \
                        const nt2_la_int* lda,                  \
                        T* ws,                                  \
                        const T* vl,                            \
                        const nt2_la_int* ldvl,                 \
                        const T* vr,                            \
                        const nt2_la_int* ldvr,                 \
                        nt2_la_int* ilo,                        \
                        nt2_la_int* ihi,                        \
                        TBASE* scale,                           \
                        TBASE* abnrm,                           \
                        TBASE* rconde,                          \
                        TBASE* rcondv,                          \
                        nt2_la_int* info,                       \
                        nt2::details::workspace<T> & w)         \
      {                                                         \
        w.resizerw(2**n);                                       \
        F77NAME( NAME )(balanc, jobvl, jobvr, sense,            \
                        n, a, lda, ws, vl, ldvl, vr, ldvr,      \
                        ilo, ihi, scale, abnrm, rconde,         \
                        rcondv, w.getw(), w.query(), w.getrw(), \
                        info);                                  \
        w.resizew(w.neededsize());                              \
        F77NAME( NAME )(balanc, jobvl, jobvr, sense,            \
                        n, a, lda, ws, vl, ldvl, vr, ldvr,      \
                        ilo, ihi, scale, abnrm, rconde,         \
                        rcondv, w.getw(),                       \
                        &w.neededsize(), w.getrw(),             \
                        info);                                  \
      }                                                         \
          inline void geevx(                                    \
                            const char* balanc,                 \
                            const char* jobvl,                  \
                            const char* jobvr,                  \
                            const char* sense,                  \
                            const nt2_la_int* n,                \
                            const T* a,                         \
                            const nt2_la_int* lda,              \
                            T* ws,                              \
                            const T* vl,                        \
                            const nt2_la_int* ldvl,             \
                            const T* vr,                        \
                            const nt2_la_int* ldvr,             \
                            nt2_la_int* ilo,                    \
                            nt2_la_int* ihi,                    \
                            TBASE* scale,                       \
                            TBASE* abnrm,                       \
                            TBASE* rconde,                      \
                            TBASE* rcondv,                      \
                            nt2_la_int* info)                   \
          {                                                     \
            nt2::details::workspace<T> w;                       \
            geevx(balanc, jobvl, jobvr, sense,                  \
                  n, a, lda, ws, vl, ldvl, vr, ldvr,            \
                  ilo, ihi, scale, abnrm, rconde,               \
                  rcondv, info, w);                             \
          }                                                     \
        /**/
    NT2_GEEVX(cgeevx, std::complex<float>, float)
    NT2_GEEVX(zgeevx, std::complex<double>, double)

#undef NT2_GEEVX
      }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of con.hpp
// /////////////////////////////////////////////////////////////////////////////
