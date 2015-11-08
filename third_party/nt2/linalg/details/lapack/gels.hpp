//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GELS_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GELS_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
/*! \file gels_itf.hh
    (excerpt adapted from xgels.f file commentaries)

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
    **  xgels solves overdetermined or underdetermined DATA TYPE linear systems
    **  involving an m-by-n matrix a, or its conjugate-transpose, using a qr
    **  or lq factorization of a.  it is assumed that a has full rank.
    **
    **  the following options are provided:
    **
    **  1. if trans = 'n' and m >= n:  find the least squares solution of
    **     an overdetermined system, i.e., solve the least squares problem
    **                  minimize || b - a*x ||.
    **
    **  2. if trans = 'n' and m < n:  find the minimum norm solution of
    **     an underdetermined system a * x = b.
    **
    **  3. if trans = 'c' and m >= n:  find the minimum norm solution of
    **     an undetermined system a**h * x = b.
    **
    **  4. if trans = 'c' and m < n:  find the least squares solution of
    **     an overdetermined system, i.e., solve the least squares problem
    **                  minimize || b - a**h * x ||.
    **
    **  several right hand side vectors b and solution vectors x can be
    **  handled in a single call; they are stored as the columns of the
    **  m-by-nrhs right hand side matrix b and the n-by-nrhs solution
    **  matrix x.
    **
    **  arguments
    **  =========
    **
    **  trans   (input) character
    **          = 'n': the linear system involves a;
    **          = 'c': the linear system involves a**h.
    **
    **  m       (input) long int
    **          the number of rows of the matrix a.  m >= 0.
    **
    **  n       (input) long int
    **          the number of columns of the matrix a.  n >= 0.
    **
    **  nrhs    (input) long int
    **          the number of right hand sides, i.e., the number of
    **          columns of the matrices b and x. nrhs >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the m-by-n matrix a.
    **            if m >= n, a is overwritten by details of its qr
    **                       factorization as returned by cgeqrf;
    **            if m <  n, a is overwritten by details of its lq
    **                       factorization as returned by cgelqf.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,m).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,nrhs)
    **          on entry, the matrix b of right hand side vectors, stored
    **          columnwise; b is m-by-nrhs if trans = 'n', or n-by-nrhs
    **          if trans = 'c'.
    **          on exit, b is overwritten by the solution vectors, stored
    **          columnwise:
    **          if trans = 'n' and m >= n, rows 1 to n of b contain the least
    **          squares solution vectors; the residual sum of squares for the
    **          solution in each column is given by the sum of squares of
    **          elements n+1 to m in that column;
    **          if trans = 'n' and m < n, rows 1 to n of b contain the
    **          minimum norm solution vectors;
    **          if trans = 'c' and m >= n, rows 1 to m of b contain the
    **          minimum norm solution vectors;
    **          if trans = 'c' and m < n, rows 1 to m of b contain the
    **          least squares solution vectors; the residual sum of squares
    **          for the solution in each column is given by the sum of
    **          squares of elements m+1 to n in that column.
    **
    **  ldb     (input) long int
    **          the leading dimension of the array b. ldb >= max(1,m,n).
    **
    **
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value
    **
**/
extern "C"
{
  void  NT2_F77NAME(cgels)(const char* trans, const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
  void  NT2_F77NAME(dgels)(const char* trans, const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           const double* a, const nt2_la_int* lda, double* b, const nt2_la_int* ldb,
                           double* work, const nt2_la_int* lwork, nt2_la_int* info);
  void  NT2_F77NAME(sgels)(const char* trans, const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           const float* a, const nt2_la_int* lda, float* b, const nt2_la_int* ldb,
                           float* work, const nt2_la_int* lwork, nt2_la_int* info);
  void  NT2_F77NAME(zgels)(const char* trans, const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* nrhs,
                           const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* b, const nt2_la_int* ldb,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
}

namespace nt2
{
  namespace details
  {


#define NT2_GELS(NAME, T)                       \
    inline void gels(const char* trans,         \
                     const nt2_la_int* m,       \
                     const nt2_la_int* n,       \
                     const nt2_la_int* nrhs,    \
                     const T* a,                \
                     const nt2_la_int* lda,     \
                     T* b,                      \
                     const nt2_la_int* ldb,     \
                     nt2_la_int* info,          \
                     workspace<T> & w)          \
    {                                           \
      NT2_F77NAME( NAME )(trans, m, n, nrhs,    \
                          a, lda, b, ldb,       \
                          w.main(), query(),    \
                          info);                \
      nt2_la_int wn = w.main_need();            \
      w.resize_main(wn);                        \
      NT2_F77NAME( NAME )(trans, m, n, nrhs,    \
                          a, lda, b, ldb,       \
                          w.main(),&wn,         \
                          info);                \
    }                                           \
        inline void gels(const char* trans,     \
                         const nt2_la_int* m,   \
                         const nt2_la_int* n,   \
                         const nt2_la_int* nrhs,\
                         const T* a,            \
                         const nt2_la_int* lda, \
                         T* b,                  \
                         const nt2_la_int* ldb, \
                         nt2_la_int* info)      \
    {                                           \
      workspace<T> w;                           \
      gels(trans, m, n, nrhs,                   \
           a, lda, b, ldb,                      \
           info, w);                            \
    }                                           \

    NT2_GELS(sgels, float)
    NT2_GELS(dgels, double)
    NT2_GELS(cgels, std::complex<float>)
    NT2_GELS(zgels, std::complex<double>)

#undef NT2_GELS
  }
}

#endif
