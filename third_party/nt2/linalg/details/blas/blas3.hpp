//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_BLAS3_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_BLAS3_HPP_INCLUDED

#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
// Real, single precision
  void NT2_F77NAME(sgemm) ( const char *transa, const char *transb
                          , const nt2_la_int* m, const nt2_la_int* n
                          , const nt2_la_int* k, const float *alpha
                          , const float *a, const nt2_la_int* lda
                          , const float *b, const nt2_la_int* ldb
                          , const float *beta
                          , float *c, const nt2_la_int* ldc
                          );

  void NT2_F77NAME(strsm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const float *alpha, const float *A, const nt2_la_int* lda,
                       float *B, const nt2_la_int* ldb);

  void NT2_F77NAME(strmm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      float *alpha, const float *A, const nt2_la_int* lda,
                      float *B, const nt2_la_int* ldb);

  void NT2_F77NAME(ssymm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const float *alpha, const float *A,
                      const nt2_la_int* lda, const float *B, const nt2_la_int* ldb,
                      const float *beta, float *C, const nt2_la_int* ldc);

  void NT2_F77NAME(ssyrk)(const char *uplo, const char *transa, const nt2_la_int* n,
                      const nt2_la_int* k, const float *alpha, const float *A,
                      const nt2_la_int* lda, const float *beta, float *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(ssyr2k)(const char *uplo, const char *transa, const nt2_la_int* n,
                       const nt2_la_int* k, const float *alpha, const float *A,
                       const nt2_la_int* lda, const float *B, const nt2_la_int* ldb,
                       const float *beta, float *C, const nt2_la_int* ldc);


// Real, double precison
  void NT2_F77NAME(dgemm)(const char *transa, const char *transb, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_int* k, const double *alpha,
                      const double *a, const nt2_la_int* lda, const double *b,
                      const nt2_la_int* ldb, const double *beta, double *c,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(dtrsm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const double *alpha, const double *A, const nt2_la_int* lda,
                       double *B, const nt2_la_int* ldb);

  void NT2_F77NAME(dtrmm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const double *alpha, const double *A, const nt2_la_int* lda,
                      double *B, const nt2_la_int* ldb);

  void NT2_F77NAME(dsymm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const double *alpha, const double *A,
                      const nt2_la_int* lda, const double *B,
                      const nt2_la_int* ldb, const double *beta, double *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(dsyrk)(const char *uplo, const char *transa, const nt2_la_int* n,
                      const nt2_la_int* k, const double *alpha, const double *A,
                      const nt2_la_int* lda, const double *beta, double *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(dsyr2k)(const char *uplo, const char *transa, const nt2_la_int* n,
                       const nt2_la_int* k, const double *alpha, const double *A,
                       const nt2_la_int* lda, const double *B, const nt2_la_int* ldb,
                       const double *beta, double *C, const nt2_la_int* ldc);

// Complex, single precision
  void NT2_F77NAME(cgemm)(const char *transa, const char *transb, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_int* k,
                      const nt2_la_complex *alpha, const nt2_la_complex *a,
                      const nt2_la_int* lda, const nt2_la_complex *b,
                      const nt2_la_int* ldb, const nt2_la_complex *beta,
                      nt2_la_complex *c, const nt2_la_int* ldc);

  void NT2_F77NAME(ctrsm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const nt2_la_complex *alpha, const nt2_la_complex *A,
                      const nt2_la_int* lda, nt2_la_complex *B,
                      const nt2_la_int* ldb);

  void NT2_F77NAME(ctrmm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      nt2_la_complex *alpha, const nt2_la_complex *A,
                      const nt2_la_int* lda, const nt2_la_complex *B,
                      const nt2_la_int* ldb);

  void NT2_F77NAME(csymm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *B, const nt2_la_int* ldb,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(chemm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *B, const nt2_la_int* ldb,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(csyrk)(const char *uplo, const char *transa, const nt2_la_int* n,
                      const nt2_la_int* k, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(csyr2k)(const char *uplo, const char *transa, const nt2_la_int* n,
                       const nt2_la_int* k, const nt2_la_complex *alpha,
                       const nt2_la_complex *A, const nt2_la_int* lda,
                       const nt2_la_complex *B, const nt2_la_int* ldb,
                       const nt2_la_complex *beta, nt2_la_complex *C,
                       const nt2_la_int* ldc);

// Complex, double precision
  void NT2_F77NAME(zgemm)(const char *transa, const char *transb, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_int* k,
                      const nt2_la_complex *alpha, const nt2_la_complex *a,
                      const nt2_la_int* lda, const nt2_la_complex *b,
                      const nt2_la_int* ldb, const nt2_la_complex *beta,
                      nt2_la_complex *c, const nt2_la_int* ldc);

  void NT2_F77NAME(ztrsm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const nt2_la_complex *alpha, const nt2_la_complex *A,
                      const nt2_la_int* lda, const nt2_la_complex *B,
                      const nt2_la_int* ldb);

  void NT2_F77NAME(ztrmm)(const char *side, const char *uplo, const char *transa,
                      const char *diag, const nt2_la_int* m, const nt2_la_int* n,
                      const nt2_la_complex *alpha, const nt2_la_complex *A,
                      const nt2_la_int* lda, const nt2_la_complex *B,
                      const nt2_la_int* ldb);

  void NT2_F77NAME(zhemm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *B, const nt2_la_int* ldb,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(zsymm)(const char *side, const char *uplo, const nt2_la_int* m,
                      const nt2_la_int* n, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *B, const nt2_la_int* ldb,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(zsyrk)(const char *uplo, const char *transa, const nt2_la_int* n,
                      const nt2_la_int* k, const nt2_la_complex *alpha,
                      const nt2_la_complex *A, const nt2_la_int* lda,
                      const nt2_la_complex *beta, nt2_la_complex *C,
                      const nt2_la_int* ldc);

  void NT2_F77NAME(zsyr2k)(const char *uplo, const char *transa, const nt2_la_int* n,
                       const nt2_la_int* k, const nt2_la_complex *alpha,
                       const nt2_la_complex *A, const nt2_la_int* lda,
                       const nt2_la_complex *B, const nt2_la_int* ldb,
                       const nt2_la_complex *beta, nt2_la_complex *C,
                       const nt2_la_int* ldc);
}

#endif
