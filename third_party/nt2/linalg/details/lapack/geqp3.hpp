//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GEQP3_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GEQP3_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
// its geqp3
//  DGEQP3 computes a QR factorization with column pivoting of a
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
// *  Further Details
// *  ===============
// *
// *  The matrix Q is represented as a product of elementary reflectors
// *
// *     Q = H(1) H(2) . . . H(k), where k = min(m,n).
// *
// *  Each H(i) has the form
// *
// *     H(i) = I - tau * v * v**T
// *
// *  where tau is a real/complex scalar, and v is a real/complex vector
// *  with v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in
// *  A(i+1:m,i), and tau in TAU(i).
// *
// *  Based on contributions by
// *    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain
// *    X. Sun, Computer Science Dept., Duke University, USA
// *
namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgeqp3)(const nt2_la_int* m, const nt2_la_int* n,
                               nt2_la_complex* a, const nt2_la_int* lda,
                               nt2_la_int* jpvt, nt2_la_complex* tau, nt2_la_complex* work,
                               const nt2_la_int* lwork, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgeqp3)(const nt2_la_int* m, const nt2_la_int* n,
                               double* a, const nt2_la_int* lda,
                               nt2_la_int* jpvt, double* tau, double* work,
                               const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(sgeqp3)(const nt2_la_int* m, const nt2_la_int* n,
                               float* a, const nt2_la_int* lda,
                               nt2_la_int* jpvt, float* tau, float* work,
                               const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(zgeqp3)(const nt2_la_int* m, const nt2_la_int* n,
                               nt2_la_complex* a, const nt2_la_int* lda,
                               nt2_la_int* jpvt, nt2_la_complex* tau, nt2_la_complex* work,
                               const nt2_la_int* lwork, double* rwork, nt2_la_int* info);
    }


#define NT2_GEQP3(NAME, T)                            \
    inline void geqp3(const nt2_la_int* m,            \
                      const nt2_la_int* n,            \
                      T* a,                           \
                      const nt2_la_int* lda,          \
                      nt2_la_int* jpvt,               \
                      T* tau,                         \
                      nt2_la_int* info,               \
                      nt2::details::workspace<T> & w) \
    {                                                 \
      NT2_F77NAME(NAME)(m,n,a,lda,jpvt,tau,           \
                        w.main(),query(),info);       \
      nt2_la_int wn = w.main_need();                  \
      w.resize_main(wn);                              \
      NT2_F77NAME(NAME)(m,n,a,lda,jpvt,tau,           \
                        w.main(),&wn,info);           \
    }                                                 \
    inline void geqp3(const nt2_la_int* m,            \
                      const nt2_la_int* n,            \
                      T* a,                           \
                      const nt2_la_int* lda,          \
                      nt2_la_int* jpvt,               \
                      T* tau,                         \
                      nt2_la_int* info)               \
    {                                                 \
      nt2::details::workspace<T> w;                   \
      geqp3(m, n, a, lda, jpvt,                       \
            tau, info, w);                            \
    }                                                 \

    NT2_GEQP3(sgeqp3, float)
    NT2_GEQP3(dgeqp3, double)

#undef NT2_GEQP3

#define NT2_GEQP3(NAME,T,TBASE)               \
    inline void geqp3(const nt2_la_int *m,    \
                      const nt2_la_int *n,    \
                      T*a,                    \
                      const nt2_la_int *lda,  \
                      nt2_la_int* jpvt,       \
                      T*tau,                  \
                      nt2_la_int *info,       \
              nt2::details::workspace<T>&w)   \
      {                                       \
        w.resize_reals(2**n);                 \
        NT2_F77NAME(NAME)(m,n,a,lda,jpvt,tau, \
                          w.main(),query(),   \
                          w.reals(),info);    \
        nt2_la_int wn = w.main_need();        \
        w.resize_main(wn);                    \
        NT2_F77NAME(NAME)(m,n,a,lda,jpvt,tau, \
                          w.main(),&wn,       \
                          w.reals(),info);    \
      }                                       \
  inline void geqp3(const nt2_la_int *m,      \
                    const nt2_la_int *n,      \
                    T*a,                      \
                    const nt2_la_int *lda,    \
                    nt2_la_int * jpvt,        \
                    T* tau,                   \
                    nt2_la_int *info)         \
  {                                           \
    nt2::details::workspace<T>w;              \
    geqp3(m,n,a,lda,jpvt,tau,info,w);         \
  }                                           \

    NT2_GEQP3(cgeqp3, std::complex<float>,  float)
    NT2_GEQP3(zgeqp3, std::complex<double>, double)

#undef NT2_GEQP3


  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of geqp3.hpp
// /////////////////////////////////////////////////////////////////////////////
