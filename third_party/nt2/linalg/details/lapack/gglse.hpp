//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GGLSE_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GGLSE_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
/*! \file gglse_itf.hh
    (excerpt adapted from xgglse.f file commentaries)

    DATA TYPE can mean float, double, std::complex<float>, std::complex<double>

    BASE TYPE can mean respectively float, double, float, double

    In some cases only two of these types types are available
    the two real or the two std::complex ones.
    CAPITALIZED PARAMETERS are FORTRAN parameters who are not used directly
    in the C++ calls, but through the workspace parameter,
    their use is transparent for the caller (see lapackworkspace.hh)

    *
    **  purpose
    **  =======
    **
    **  xgglse solves the linear equality-constrained least squares (lse)
    **  problem:
    **
    **          minimize || c - a*x ||_2   subject to   b*x = d
    **
    **  where a is an m-by-n matrix, b is a p-by-n matrix, c is a given
    **  m-vector, and d is a given p-vector. it is assumed that
    **  p <= n <= m+p, and
    **
    **           rank(b) = p and  rank( ( a ) ) = n.
    **                                ( ( b ) )
    **
    **  these conditions ensure that the lse problem has a unique solution,
    **  which is obtained using a grq factorization of the matrices b and a.
    **
    **  arguments
    **  =========
    **
    **  m       (input) nt2_la_int
    **          the number of rows of the matrix a.  m >= 0.
    **
    **  n       (input) nt2_la_int
    **          the number of columns of the matrices a and b. n >= 0.
    **
    **  p       (input) nt2_la_int
    **          the number of rows of the matrix b. 0 <= p <= n <= m+p.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the m-by-n matrix a.
    **          on exit, a is destroyed.
    **
    **  lda     (input) nt2_la_int
    **          the leading dimension of the array a. lda >= max(1,m).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,n)
    **          on entry, the p-by-n matrix b.
    **          on exit, b is destroyed.
    **
    **  ldb     (input) nt2_la_int
    **          the leading dimension of the array b. ldb >= max(1,p).
    **
    **  c       (input/output) DATA TYPE array, dimension (m)
    **          on entry, c contains the right hand side vector for the
    **          least squares part of the lse problem.
    **          on exit, the residual sum of squares for the solution
    **          is given by the sum of squares of elements n-p+1 to m of
    **          vector c.
    **
    **  d       (input/output) DATA TYPE array, dimension (p)
    **          on entry, d contains the right hand side vector for the
    **          constrained equation.
    **          on exit, d is destroyed.
    **
    **  x       (output) DATA TYPE array, dimension (n)
    **          on exit, x is the solution of the lse problem.
    **
    **
    **
    **  info    (output) nt2_la_int
    **          = 0:  successful exit.
    **          < 0:  if info = -i, the i-th argument had an illegal value.
    **
**/
/////////////////////////////////////////////////////////////////////////////////

extern "C"
{
  void NT2_F77NAME(cgglse)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* p,
                           nt2_la_complex* a, const nt2_la_int* lda,
                           nt2_la_complex* b, const nt2_la_int* ldb,
                           nt2_la_complex* c, nt2_la_complex* d, nt2_la_complex* x,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(dgglse)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* p,
                           double* a, const nt2_la_int* lda,
                           double* b, const nt2_la_int* ldb,
                           double* c, double* d, double* x,
                           double* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(sgglse)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* p,
                           float* a, const nt2_la_int* lda,
                           float* b, const nt2_la_int* ldb,
                           float* c, float* d, float* x,
                           float* work, const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(zgglse)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* p,
                           nt2_la_complex* a, const nt2_la_int* lda,
                           nt2_la_complex* b, const nt2_la_int* ldb,
                           nt2_la_complex* c, nt2_la_complex* d, nt2_la_complex* x,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
}

namespace nt2
{
  namespace details
  {
  /////////////////////////////////////////////////////////////////////////
  // (excerpt adapted from sgglse.f)
  //    *  WORK    (workspace/output) float array, dimension (LWORK)
  //    *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //    *
  //    *  LWORK   (input) nt2_la_int
  //    *          The dimension of the array WORK. LWORK >= max(1,M+N+P).
  //    *          For optimum performance LWORK >= P+min(M,N)+max(M,N)*NB,
  //    *          where NB is an upper bound for the optimal blocksizes for
  //    *          SGEQRF, SGERQF, SORMQR and SORMRQ.
  //    *
  //    *          If LWORK = -1, then a workspace query is assumed; the routine
  //    *          only calculates the optimal size of the WORK array, returns
  //    *          this value as the first entry of the WORK array, and no error
  //    *          message related to LWORK is issued by XERBLA.
  //    *
  /////////////////////////////////////////////////////////////////////////

#define NT2_GGLSE(NAME, T)                      \
  inline void gglse(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* p,        \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    T* c,                       \
                    T* d,                 \
                    T* x,                       \
                    nt2_la_int* info,           \
            nt2::details::workspace<T> & w)     \
  {                                             \
    NT2_F77NAME( NAME )(m, n, p, a, lda,        \
                        b, ldb,                 \
                        c, d, x, w.main(),      \
                        query(), info);         \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(m, n, p, a, lda,        \
                        b, ldb,                 \
                        c, d, x, w.main(),      \
                        &wn, info);             \
  }                                             \
  inline void gglse(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* p,        \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    T* c,                       \
                    T* d,                 \
                    T* x,                       \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gglse(m, n, p,                              \
          a, lda, b, ldb,                       \
          c, d, x, info, w);                    \
  }                                             \

    NT2_GGLSE(sgglse, float)
    NT2_GGLSE(dgglse, double)

#undef NT2_GGLSE

  /////////////////////////////////////////////////////////////////////////
  // (excerpt adapted from cgglse.f)
  //    *  WORK    (workspace/output) std::complex<float> array, dimension (LWORK)
  //    *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //    *
  //    *  LWORK   (input) nt2_la_int
  //    *          The dimension of the array WORK. LWORK >= max(1,M+N+P).
  //    *          For optimum performance LWORK >= P+min(M,N)+max(M,N)*NB,
  //    *          where NB is an upper bound for the optimal blocksizes for
  //    *          CGEQRF, CGERQF, CUNMQR and CUNMRQ.
  //    *
  //    *          If LWORK = -1, then a workspace query is assumed; the routine
  //    *          only calculates the optimal size of the WORK array, returns
  //    *          this value as the first entry of the WORK array, and no error
  //    *          message related to LWORK is issued by XERBLA.
  //    *
  /////////////////////////////////////////////////////////////////////////

#define NT2_GGLSE(NAME, T, TBASE)               \
  inline void gglse(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* p,        \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    T* c,                       \
                    T* d,                 \
                    T* x,                       \
                    nt2_la_int* info,           \
            nt2::details::workspace<T> & w)     \
  {                                             \
    NT2_F77NAME( NAME )(m, n, p,                \
                        a, lda, b, ldb,         \
                        c, d, x, w.main(),      \
                        query(), info);         \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(m, n, p,                \
                        a, lda, b, ldb,         \
                        c, d, x, w.main(),      \
                        &wn, info);             \
  }                                             \
  inline void gglse(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* p,        \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    T* c,                       \
                    T* d,                       \
                    T* x,                       \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gglse(m, n, p, a, lda,                      \
          b, ldb, c, d,                         \
          x, info, w);                          \
  }                                             \

    NT2_GGLSE(cgglse, std::complex<float>,  float)
    NT2_GGLSE(zgglse, std::complex<double>, double)

#undef NT2_GGLSE

      }
}
#endif
