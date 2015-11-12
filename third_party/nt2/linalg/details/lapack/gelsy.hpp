//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GELSY_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GELSY_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

/*! \file gelsy_itf.hh
    (excerpt adapted from xgelsy.f file commentaries)

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
    **  xgelsy computes the minimum-norm solution to a DATA TYPE linear least
    **  squares problem:
    **      minimize || a * x - b ||
    **  using a complete orthogonal factorization of a.  a is an m-by-n
    **  matrix which may be rank-deficient.
    **
    **  several right hand side vectors b and solution vectors x can be
    **  handled in a single call; they are stored as the columns of the
    **  m-by-nrhs right hand side matrix b and the n-by-nrhs solution
    **  matrix x.
    **
    **  the routine first computes a qr factorization with column pivoting:
    **      a * p = q * [ r11 r12 ]
    **                  [  0  r22 ]
    **  with r11 defined as the largest leading submatrix whose estimated
    **  condition number is less than 1/rcond.  the order of r11, rank,
    **  is the effective rank of a.
    **
    **  then, r22 is considered to be negligible, and r12 is annihilated
    **  by unitary transformations from the right, arriving at the
    **  complete orthogonal factorization:
    **     a * p = q * [ t11 0 ] * z
    **                 [  0  0 ]
    **  the minimum-norm solution is then
    **     x = p * z' [ inv(t11)*q1'*b ]
    **                [        0       ]
    **  where q1 consists of the first rank columns of q.
    **
    **  this routine is basically identical to the original xgelsx except
    **  three differences:
    **    o the permutation of matrix b (the right hand side) is faster and
    **      more simple.
    **    o the call to the subroutine xgeqpf has been substituted by the
    **      the call to the subroutine xgeqp3. this subroutine is a blas-3
    **      version of the qr factorization with column pivoting.
    **    o matrix b (the right hand side) is updated with blas-3.
    **
    **  arguments
    **  =========
    **
    **  m       (input) long int
    **          the number of rows of the matrix a.  m >= 0.
    **
    **  n       (input) long int
    **          the number of columns of the matrix a.  n >= 0.
    **
    **  nrhs    (input) long int
    **          the number of right hand sides, i.e., the number of
    **          columns of matrices b and x. nrhs >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the m-by-n matrix a.
    **          on exit, a has been overwritten by details of its
    **          complete orthogonal factorization.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,m).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,nrhs)
    **          on entry, the m-by-nrhs right hand side matrix b.
    **          on exit, the n-by-nrhs solution matrix x.
    **
    **  ldb     (input) long int
    **          the leading dimension of the array b. ldb >= max(1,m,n).
    **
    **  jpvt    (input/output) long int array, dimension (n)
    **          on entry, if jpvt(i) .ne. 0, the i-th column of a is permuted
    **          to the front of ap, otherwise column i is a free column.
    **          on exit, if jpvt(i) = k, then the i-th column of a*p
    **          was the k-th column of a.
    **
    **  rcond   (input) BASE DATA TYPE
    **          rcond is used to determine the effective rank of a, which
    **          is defined as the order of the largest leading triangular
    **          submatrix r11 in the qr factorization with pivoting of a,
    **          whose estimated condition number < 1/rcond.
    **
    **  rank    (output) long int
    **          the effective rank of a, i.e., the order of the submatrix
    **          r11.  this is the same as the order of the submatrix t11
    **          in the complete orthogonal factorization of a.
    **
    **
    **
    **
    **  info    (output) long int
    **          = 0: successful exit
    **          < 0: if info = -i, the i-th argument had an illegal value
    **
    **  further details
    **  ===============
    **
    **  based on contributions by
    **    a. petitet, computer science dept., univ. of tenn., knoxville, usa
    **    e. quintana-orti, depto. de informatica, universidad jaime i, spain
    **    g. quintana-orti, depto. de informatica, universidad jaime i, spain
    **
**/
/////////////////////////////////////////////////////////////////////////////////


namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgelsy)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                               nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_int* jpvt, const float* rcond, nt2_la_int* rank,
                               nt2_la_complex* work, const nt2_la_int* lwork, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgelsy)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                               double* a, const nt2_la_int* lda, double* b, const nt2_la_int* ldb,
                               nt2_la_int* jpvt, const double* rcond, nt2_la_int* rank,
                               double* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(sgelsy)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                               float* a, const nt2_la_int* lda, float* b, const nt2_la_int* ldb,
                               nt2_la_int* jpvt, const float* rcond, nt2_la_int* rank,
                               float* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(zgelsy)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                               nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_int* jpvt, const double* rcond, nt2_la_int* rank,
                               nt2_la_complex* work, const nt2_la_int* lwork, double* rwork, nt2_la_int* info);
    }


  /////////////////////////////////////////////////////////////////////////
  // (excerpt adapted from sgelsy.f)
  //    *  WORK    (workspace/output) float array, dimension (LWORK)
  //    *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //    *
  //    *  LWORK   (input) nt2_la_int
  //    *          The dimension of the array WORK.
  //    *          The unblocked strategy requires that:
  //    *             LWORK >= MAX( MN+3*N+1, 2*MN+NRHS ),
  //    *          where MN = min( M, N ).
  //    *          The block algorithm requires that:
  //    *             LWORK >= MAX( MN+2*N+NB*(N+1), 2*MN+NB*NRHS ),
  //    *          where NB is an upper bound on the blocksize returned
  //    *          by ILAENV for the routines SGEQP3, STZRZF, STZRQF, SORMQR,
  //    *          and SORMRZ.
  //    *
  //    *          If LWORK = -1, then a workspace query is assumed; the routine
  //    *          only calculates the optimal size of the WORK array, returns
  //    *          this value as the first entry of the WORK array, and no error
  //    *          message related to LWORK is issued by XERBLA.
  //    *
  /////////////////////////////////////////////////////////////////////////

#define NT2_GELSY(NAME, T)                      \
  inline void gelsy(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    nt2_la_int* jpvt,           \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info,           \
                    workspace<T> & w)           \
  {                                             \
    NT2_F77NAME(NAME)(m, n, nrhs,               \
                      a, lda, b, ldb,           \
                      jpvt, rcond, rank,        \
                      w.main(), query(),        \
                      info);                    \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME(NAME)(m, n, nrhs,               \
                      a, lda, b, ldb,           \
                      jpvt, rcond, rank,        \
                      w.main(), &wn, info);     \
  }                                             \
  inline void gelsy(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    nt2_la_int* jpvt,           \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info)           \
  {                                             \
    workspace<T> w;                             \
    gelsy(m, n, nrhs,                           \
          a, lda, b, ldb,                       \
          jpvt, rcond,                          \
          rank, info, w);                       \
  }                                             \

    NT2_GELSY(sgelsy, float)
    NT2_GELSY(dgelsy, double)

#undef NT2_GELSY

  /////////////////////////////////////////////////////////////////////////
  // (excerpt adapted from cgelsy.f)
  //    *  WORK    (workspace/output) std::complex<float> array, dimension (LWORK)
  //    *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //    *
  //    *  LWORK   (input) nt2_la_int
  //    *          The dimension of the array WORK.
  //    *          The unblocked strategy requires that:
  //    *            LWORK >= MN + MAX( 2*MN, N+1, MN+NRHS )
  //    *          where MN = min(M,N).
  //    *          The block algorithm requires that:
  //    *            LWORK >= MN + MAX( 2*MN, NB*(N+1), MN+MN*NB, MN+NB*NRHS )
  //    *          where NB is an upper bound on the blocksize returned
  //    *          by ILAENV for the routines CGEQP3, CTZRZF, CTZRQF, CUNMQR,
  //    *          and CUNMRZ.
  //    *
  //    *          If LWORK = -1, then a workspace query is assumed; the routine
  //    *          only calculates the optimal size of the WORK array, returns
  //    *          this value as the first entry of the WORK array, and no error
  //    *          message related to LWORK is issued by XERBLA.
  //    *
  //    *  RWORK   (workspace) float array, dimension (2*N)
  //    *
  /////////////////////////////////////////////////////////////////////////

#define NT2_GELSY(NAME, T, TBASE)               \
   inline void gelsy(const nt2_la_int* m,       \
                     const nt2_la_int* n,       \
                     const nt2_la_int* nrhs,    \
                     T* a,                      \
                     const nt2_la_int* lda,     \
                     T* b,                      \
                     const nt2_la_int* ldb,     \
                     nt2_la_int* jpvt,          \
                     const TBASE* rcond,        \
                     nt2_la_int* rank,          \
                     nt2_la_int* info,          \
                     workspace<T> & w)          \
   {                                            \
     w.resize_reals(2**n);                      \
     NT2_F77NAME( NAME )(m, n, nrhs,            \
                         a, lda, b, ldb,        \
                         jpvt, rcond, rank,     \
                         w.main(), query(),     \
                         w.reals(), info);      \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        jpvt, rcond, rank,      \
                        w.main(), &wn,          \
                        w.reals(), info);       \
   }                                            \
   inline void gelsy(const nt2_la_int* m,       \
                     const nt2_la_int* n,       \
                     const nt2_la_int* nrhs,    \
                     T* a,                      \
                     const nt2_la_int* lda,     \
                     T* b,                      \
                     const nt2_la_int* ldb,     \
                     nt2_la_int* jpvt,          \
                     const TBASE* rcond,        \
                     nt2_la_int* rank,          \
                     nt2_la_int* info)          \
   {                                            \
     workspace<T> w;                            \
     gelsy(m, n, nrhs,                          \
           a, lda, b, ldb,                      \
           jpvt, rcond,                         \
           rank, info, w);                      \
   }                                            \

    NT2_GELSY(cgelsy, std::complex<float>,  float)
    NT2_GELSY(zgelsy, std::complex<double>, double)

#undef NT2_GELSY

      }
}


#endif
