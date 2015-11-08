//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GESV_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GESV_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
/*! \file gesv_itf.hh
    (excerpt adapted from xgesv.f file commentaries)

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
    **  xgesv computes the solution to a DATA TYPE system of linear equations
    **     a * x = b,
    **  where a is an n-by-n matrix and x and b are n-by-nrhs matrices.
    **
    **  the lu decomposition with partial pivoting and row interchanges is
    **  used to factor a as
    **     a = p * l * u,
    **  where p is a permutation matrix, l is unit lower triangular, and u is
    **  upper triangular.  the factored form of a is then used to solve the
    **  system of equations a * x = b.
    **
    **  arguments
    **  =========
    **
    **  n       (input) long int
    **          the number of linear equations, i.e., the order of the
    **          matrix a.  n >= 0.
    **
    **  nrhs    (input) long int
    **          the number of right hand sides, i.e., the number of columns
    **          of the matrix b.  nrhs >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the n-by-n coefficient matrix a.
    **          on exit, the factors l and u from the factorization
    **          a = p*l*u; the unit diagonal elements of l are not stored.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,n).
    **
    **  ipiv    (output) long int array, dimension (n)
    **          the pivot indices that define the permutation matrix p;
    **          row i of the matrix was interchanged with row ipiv(i).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,nrhs)
    **          on entry, the n-by-nrhs matrix of right hand side matrix b.
    **          on exit, if info = 0, the n-by-nrhs solution matrix x.
    **
    **  ldb     (input) long int
    **          the leading dimension of the array b.  ldb >= max(1,n).
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value
    **          > 0:  if info = i, u(i,i) is exactly zero.  the factorization
    **                has been completed, but the factor u is exactly
    **                singular, so the solution could not be computed.
    **
**/
extern "C"
{
  void NT2_F77NAME(cgesv)(const nt2_la_int* n, const nt2_la_int* nrhs,
                          nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* ipiv,
                          nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(dgesv)(const nt2_la_int* n, const nt2_la_int* nrhs,
                          double* a, const nt2_la_int* lda, nt2_la_int* ipiv,
                          double* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(sgesv)(const nt2_la_int* n, const nt2_la_int* nrhs,
                          float* a, const nt2_la_int* lda, nt2_la_int* ipiv,
                          float* b, const nt2_la_int* ldb, nt2_la_int* info);
  void NT2_F77NAME(zgesv)(const nt2_la_int* n, const nt2_la_int* nrhs,
                          nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* ipiv,
                          nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info);
}

namespace nt2
{
  namespace details
  {

#define NT2_GESV(NAME, T)                         \
  inline void gesv(const nt2_la_int* n,           \
                   const nt2_la_int* nrhs,        \
                   T* a,                          \
                   const nt2_la_int* lda,         \
                   nt2_la_int* ipiv,              \
                   T* b,                          \
                   const nt2_la_int* ldb,         \
                   nt2_la_int* info,              \
                   nt2::details::workspace<T> & ) \
  {                                               \
      NT2_F77NAME( NAME )(n, nrhs, a, lda,        \
                          ipiv, b, ldb, info);    \
    }                                             \
    inline void gesv(const nt2_la_int* n,         \
                     const nt2_la_int* nrhs,      \
                     T* a,                        \
                     const nt2_la_int* lda,       \
                     nt2_la_int* ipiv,            \
                     T* b,                        \
                     const nt2_la_int* ldb,       \
                     nt2_la_int* info)            \
    {                                             \
      NT2_F77NAME( NAME )(n, nrhs, a, lda,        \
                          ipiv, b, ldb, info);    \
    }                                             \


    NT2_GESV(sgesv, float)
    NT2_GESV(dgesv, double)
    NT2_GESV(cgesv, std::complex<float>)
    NT2_GESV(zgesv, std::complex<double>)

#undef NT2_GESV
  }
}

#endif

