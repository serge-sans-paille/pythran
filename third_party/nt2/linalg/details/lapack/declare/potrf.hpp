//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_POTRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_POTRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/// Lapack declaration interface
///
/// excerpt from LAPACK documentation
/// FOR ? C or Z
// *  Purpose
// *  =======
//
//  ?POTRF computes the Cholesky factorization of a real symmetric/complex hermitian
//  positive definite matrix A.

//  The factorization has the form
//  A = U**T * U, if UPLO = 'U', or
//  A = L * L**T, if UPLO = 'L',
//  where U is an upper triangular matrix and L is lower triangular.

//  This is the block version of the algorithm, calling Level 3 BLAS.
//  \endverbatim

// Arguments:
// ==========

//  \param[in] UPLO
//  \verbatim
//  UPLO is CHARACTER*1
//  = 'U': Upper triangle of A is stored;
//  = 'L': Lower triangle of A is stored.
//  \endverbatim

//  \param[in] N
//  \verbatim
//  N is INTEGER
//  The order of the matrix A. N >= 0.
//  \endverbatim

//  \param[in,out] A
//  \verbatim
//  A is REAL/COMPLEX array, dimension (LDA,N)
//  On entry, the symmetric matrix A. If UPLO = 'U', the leading
//  N-by-N upper triangular part of A contains the upper
//  triangular part of the matrix A, and the strictly lower
//  triangular part of A is not referenced. If UPLO = 'L', the
//  leading N-by-N lower triangular part of A contains the lower
//  triangular part of the matrix A, and the strictly upper
//  triangular part of A is not referenced.

//  On exit, if INFO = 0, the factor U or L from the Cholesky
//  factorization A = U**T*U or A = L*L**T.
//  \endverbatim

//  \param[in] LDA
//  \verbatim
//  LDA is INTEGER
//  The leading dimension of the array A. LDA >= max(1,N).
//  \endverbatim

//  \param[out] INFO
//  \verbatim
//  INFO is INTEGER
//  = 0: successful exit
//  < 0: if INFO = -i, the i-th argument had an illegal value
//  > 0: if INFO = i, the leading minor of order i is not
//  positive definite, and the factorization could not be
//  completed.
//  \endverbatim


extern "C"
{
  void NT2_F77NAME(dpotrf)( const char* uplo, const nt2_la_int* n
                          , double* a       , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(spotrf)( const char* uplo, const nt2_la_int* n
                          , float* a        , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(cpotrf)( const char* uplo  , const nt2_la_int* n
                          , nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_int* info
                          );

  void NT2_F77NAME(zpotrf)(const char* uplo   , const nt2_la_int* n
                          , nt2_la_complex* a , const nt2_la_int* lda
                          , nt2_la_int* info
                          );
}

#endif
