//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GETRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GETRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? C or Z
// *  ?GETRF computes an LU factorization of a general M-by-N matrix A
// *  using partial pivoting with row interchanges.
// *
// *  The factorization has the form
// *     A = P * L * U
// *  where P is a permutation matrix, L is lower triangular with unit
// *  diagonal elements (lower trapezoidal if m > n), and U is upper
// *  triangular (upper trapezoidal if m < n).
// *
// *  This is the right-looking Level 3 BLAS version of the algorithm.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A.  M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) COMPLEX array, dimension (LDA,N)
// *          On entry, the M-by-N matrix to be factored.
// *          On exit, the factors L and U from the factorization
// *          A = P*L*U; the unit diagonal elements of L are not stored.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,M).
// *
// *  IPIV    (output) INTEGER array, dimension (min(M,N))
// *          The pivot indices; for 1 <= i <= min(M,N), row i of the
// *          matrix was interchanged with row IPIV(i).
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value
// *          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
// *                has been completed, but the factor U is exactly
// *                singular, and division by zero will occur if it is used
// *                to solve a system of equations.
///////////////////////////////////////////////////////////////////////
/// FOR ? S or D

// *  DXGETRF computes an LU factorization of a general M-by-N matrix A
// *  using partial pivoting with row interchanges.
// *
// *  The factorization has the form
// *     A = P * L * U
// *  where P is a permutation matrix, L is lower triangular with unit
// *  diagonal elements (lower trapezoidal if m > n), and U is upper
// *  triangular (upper trapezoidal if m < n).
// *
// *  This is the right-looking Level 3 BLAS version of the algorithm.
// *
// *  Arguments
// *  =========
// *
// *  M       (input) INTEGER
// *          The number of rows of the matrix A.  M >= 0.
// *
// *  N       (input) INTEGER
// *          The number of columns of the matrix A.  N >= 0.
// *
// *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
// *          On entry, the M-by-N matrix to be factored.
// *          On exit, the factors L and U from the factorization
// *          A = P*L*U; the unit diagonal elements of L are not stored.
// *
// *  LDA     (input) INTEGER
// *          The leading dimension of the array A.  LDA >= max(1,M).
// *
// *  IPIV    (output) INTEGER array, dimension (min(M,N))
// *          The pivot indices; for 1 <= i <= min(M,N), row i of the
// *          matrix was interchanged with row IPIV(i).
// *
// *  INFO    (output) INTEGER
// *          = 0:  successful exit
// *          < 0:  if INFO = -i, the i-th argument had an illegal value
// *          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
// *                has been completed, but the factor U is exactly
// *                singular, and division by zero will occur if it is used
// *                to solve a system of equations.
// *
extern "C"

{
  void NT2_F77NAME(dgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , double* a           , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );

  void NT2_F77NAME(sgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , float* a            , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );
  void NT2_F77NAME(cgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , nt2_la_complex* a   , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );
  void NT2_F77NAME(zgetrf)( const nt2_la_int* m , const nt2_la_int* n
                          , nt2_la_complex* a   , const nt2_la_int* lda
                          , nt2_la_int* ipiv    , nt2_la_int* info
                          );
}

#endif
