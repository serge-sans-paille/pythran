//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GELSD_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GELSD_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/envblocksize.hpp>
#include <nt2/include/functions/scalar/max.hpp>

/*! \file gelsd_itf.hh
    (excerpt adapted from xgelsd.f file commentaries)

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
    **  xgelsd computes the minimum-norm solution to a BASE DATA TYPE linear least
    **  squares problem:
    **      minimize 2-norm(| b - a*x |)
    **  using the singular value decomposition (svd) of a. a is an m-by-n
    **  matrix which may be rank-deficient.
    **
    **  several right hand side vectors b and solution vectors x can be
    **  handled in a single call; they are stored as the columns of the
    **  m-by-nrhs right hand side matrix b and the n-by-nrhs solution
    **  matrix x.
    **
    **  the problem is solved in three steps:
    **  (1) reduce the coefficient matrix a to bidiagonal form with
    **      householder tranformations, reducing the original problem
    **      into a "bidiagonal least squares problem" (bls)
    **  (2) solve the bls using a divide and conquer approach.
    **  (3) apply back all the householder tranformations to solve
    **      the original least squares problem.
    **
    **  the effective rank of a is determined by treating as zero those
    **  singular values which are less than rcond times the largest singular
    **  value.
    **
    **  the divide and conquer algorithm makes very mild assumptions about
    **  floating point arithmetic. it will WORK on machines with a guard
    **  digit in add/subtract, or on those binary machines without guard
    **  digits which subtract like the cray x-mp, cray y-mp, cray c-90, or
    **  cray-2. it could conceivably fail on hexadecimal or decimal machines
    **  without guard digits, but we know of none.
    **
    **  arguments
    **  =========
    **
    **  m       (input) nt2_la_int
    **          the number of rows of the matrix a. m >= 0.
    **
    **  n       (input) nt2_la_int
    **          the number of columns of the matrix a. n >= 0.
    **
    **  nrhs    (input) nt2_la_int
    **          the number of right hand sides, i.e., the number of columns
    **          of the matrices b and x. nrhs >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the m-by-n matrix a.
    **          on exit, the first min(m,n) rows of a are overwritten with
    **          its right singular vectors, stored rowwise.
    **
    **  lda     (input) nt2_la_int
    **          the leading dimension of the array a. lda >= max(1,m).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,nrhs)
    **          on entry, the m-by-nrhs right hand side matrix b.
    **          on exit, b is overwritten by the n-by-nrhs solution matrix x.
    **          if m >= n and rank = n, the residual sum-of-squares for
    **          the solution in the i-th column is given by the sum of
    **          squares of elements n+1:m in that column.
    **
    **  ldb     (input) nt2_la_int
    **          the leading dimension of the array b.  ldb >= max(1,m,n).
    **
    **  s       (output) BASE DATA TYPE array, dimension (min(m,n))
    **          the singular values of a in decreasing order.
    **          the condition number of a in the 2-norm = s(1)/s(min(m,n)).
    **
    **  rcond   (input) BASE DATA TYPE
    **          rcond is used to determine the effective rank of a.
    **          singular values s(i) <= rcond*s(1) are treated as zero.
    **          if rcond < 0, machine precision is used instead.
    **
    **  rank    (output) nt2_la_int
    **          the effective rank of a, i.e., the number of singular values
    **          which are greater than rcond*s(1).
    **
    **
    **
    **
    **
    **  info    (output) nt2_la_int
    **          = 0: successful exit
    **          < 0: if info = -i, the i-th argument had an illegal value.
    **          > 0:  the algorithm for computing the svd failed to converge;
    **                if info = i, i off-diagonal elements of an intermediate
    **                bidiagonal form did not converge to zero.
    **
    **  further details
    **  ===============
    **
    **  based on contributions by
    **     ming gu and ren-cang li, computer science division, university of
    **       california at berkeley, usa
    **     osni marques, lbnl/nersc, usa
    **
**/
extern "C"
{
  void NT2_F77NAME(cgelsd)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                           const float* s, const float* rcond, nt2_la_int* rank, nt2_la_complex* work,
                           const nt2_la_int* lwork, float* rwork, nt2_la_int* iwork, nt2_la_int* info);
  void NT2_F77NAME(sgelsd)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           float* a, const nt2_la_int* lda, float* b, const nt2_la_int* ldb,
                           const float* s, const float* rcond, nt2_la_int* rank, float* work,
                           const nt2_la_int* lwork, nt2_la_int* iwork, nt2_la_int* info);
  void NT2_F77NAME(zgelsd)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                           const double* s, const double* rcond, nt2_la_int* rank, nt2_la_complex* work,
                           const nt2_la_int* lwork, double* rwork, nt2_la_int* iwork, nt2_la_int* info);
  void NT2_F77NAME(dgelsd)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           double* a, const nt2_la_int* lda, double* b, const nt2_la_int* ldb,
                           const double* s, const double* rcond, nt2_la_int* rank, double* work,
                           const nt2_la_int* lwork, nt2_la_int* iwork, nt2_la_int* info);
}


namespace nt2 { namespace details
{

  struct gelsdUtils
  {
    static inline nt2_la_int nlvl(const std::string & name, nt2_la_int minnm, nt2_la_int)
    {
      std::string blank =  " ";
      minnm = minnm < 1 ? 1 : minnm;
      nt2_la_int smlsiz = EnvBlockSize(9, name.c_str(), blank,0, 0, 0, 0);
      return (nt2_la_int)nt2::max( int(std::log(double(minnm))/ double(smlsiz+1))/std::log(2.0)+1,0.0);
    }

    static inline size_t liwork(const std::string & name, nt2_la_int n,  nt2_la_int m, nt2_la_int nrsh)
    {
      nt2_la_int minnm = std::min(n, m);
      return (3*nlvl(name, minnm, nrsh)+11)*minnm;
    }

    static inline nt2_la_int lrwork(const std::string & name, nt2_la_int n,  nt2_la_int m, nt2_la_int nrsh)
    {
      std::string blank =  " ";
      nt2_la_int maxnm = std::max(n, m);
      nt2_la_int minnm = std::min(n, m);
      nt2_la_int nl = nlvl(name, minnm, nrsh);
      nt2_la_int smlsiz = EnvBlockSize(9, name.c_str(), blank,0, 0, 0, 0);
      return 10*maxnm + 2*maxnm*smlsiz + 8*m*nl + 3*smlsiz*nrsh +  (smlsiz+1)*(smlsiz+1);
    }
  };
#ifndef NT2_LAPACK_3_2_WORKAROUND
  /**/
  #define NT2_GELSD(NAME, T)                    \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const T* s,                 \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info,           \
     nt2::details::workspace<T> & w)            \
  {                                             \
    nt2_la_int isize;                           \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), query(),      \
                        &isize,                 \
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    w.resize_integers(isize);                   \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), &wn,          \
                        w.integers(), info);    \
  }                                             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const T* s,                 \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gelsd(m, n, nrhs,                           \
          a, lda, b, ldb,                       \
          s, rcond, rank,                       \
          info, w);                             \
  }                                             \
  /**/
#else
  /**/
  #define NT2_GELSD(NAME, T)                    \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const T* s,                 \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info,           \
     nt2::details::workspace<T> & w)            \
  {                                             \
    nt2_la_int isize;                           \
    w.resize_integers(gelsdUtils::liwork(       \
                        "NAME",                 \
                         *n, *m, *nrhs));       \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), query(),      \
                        &isize,                 \
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), &wn,          \
                        w.integers(), info);    \
  }                                             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const T* s,                 \
                    const T* rcond,             \
                    nt2_la_int* rank,           \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gelsd(m, n, nrhs,                           \
          a, lda, b, ldb,                       \
          s, rcond, rank,                       \
          info, w);                             \
  }                                             \
/**/
#endif

    NT2_GELSD(sgelsd, float)
    NT2_GELSD(dgelsd, double)

#undef NT2_GELSD

#ifndef NT2_LAPACK_3_2_WORKAROUND
  #define NT2_GELSD(NAME, T, TBASE)             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const TBASE* s,             \
                    const TBASE* rcond,         \
                    nt2_la_int* rank,           \
                    nt2_la_int* info,           \
      nt2::details::workspace<T> & w)           \
  {                                             \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), query(),      \
                        w.reals(), w.integers(),\
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    nt2_la_int wi = w.reals_need();             \
    w.resize_reals(wi);                         \
    nt2_la_int wr = w.integers_need();          \
    w.resize_integers(wr);                      \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), &wn,          \
                        w.reals(),              \
                        w.integers(), info);    \
  }                                             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const TBASE* s,             \
                    const TBASE* rcond,         \
                    nt2_la_int* rank,           \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gelsd(m, n, nrhs,                           \
          a, lda, b, ldb,                       \
          s, rcond, rank,                       \
          info, w);                             \
  }                                             \
  /**/
#else
    /**/
  #define NT2_GELSD(NAME, T, TBASE)             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const TBASE* s,             \
                    const TBASE* rcond,         \
                    nt2_la_int* rank,           \
                    nt2_la_int* info,           \
      nt2::details::workspace<T> & w)           \
  {                                             \
    w.resize_integers(gelsdUtils::liwork("NAME",\
                         *n, *m, *nrhs));       \
    w.resize_reals(gelsdUtils::lrwork("NAME",   \
                              *n, *m, *nrhs));  \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), query(),      \
                        w.reals(), w.integers(),\
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(m, n, nrhs,             \
                        a, lda, b, ldb,         \
                        s, rcond, rank,         \
                        w.main(), &wn,          \
                        w.reals(),              \
                        w.integers(), info);    \
  }                                             \
  inline void gelsd(const nt2_la_int* m,        \
                    const nt2_la_int* n,        \
                    const nt2_la_int* nrhs,     \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* b,                       \
                    const nt2_la_int* ldb,      \
                    const TBASE* s,             \
                    const TBASE* rcond,         \
                    nt2_la_int* rank,           \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gelsd(m, n, nrhs,                           \
          a, lda, b, ldb,                       \
          s, rcond, rank,                       \
          info, w);                             \
  }                                             \
    /**/
#endif

    NT2_GELSD(cgelsd, std::complex<float>,  float)
    NT2_GELSD(zgelsd, std::complex<double>, double)

#undef NT2_GELSD
      }
}

#endif
