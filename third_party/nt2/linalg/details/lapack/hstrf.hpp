//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_HSTRF_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_HSTRF_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/include/functions/scalar/max.hpp>
// contrarily to lapack we use sym mtrix in real case ans hermitian in complex case
// this means that hstrf calls respectively xsytrf ans xhetrf
//     **  purpose
//     **  =======
//     **
//     **  xsytrf computes the factorization of a DATA TYPE symmetric matrix a
//     **  using the bunch-kaufman diagonal pivoting method.  the form of the
//     **  factorization is
//     **
//     **     a = u*d*u**t  or  a = l*d*l**t
//     **
//     **  where u (or l) is a product of permutation and unit upper (lower)
//     **  triangular matrices, and d is symmetric and block diagonal with
//     **  with 1-by-1 and 2-by-2 diagonal blocks.
//     **
//     **  this is the blocked version of the algorithm, calling level 3 blas.
//     **
//     **  arguments
//     **  =========
//     **
//     **  uplo    (input) char
//     **          = 'u':  upper triangle of a is stored;
//     **          = 'l':  lower triangle of a is stored.
//     **
//     **  n       (input) long int
//     **          the order of the matrix a.  n >= 0.
//     **
//     **  a       (input/output) DATA TYPE array, dimension (lda,n)
//     **          on entry, the symmetric matrix a.  if uplo = 'u', the leading
//     **          n-by-n upper triangular part of a contains the upper
//     **          triangular part of the matrix a, and the strictly lower
//     **          triangular part of a is not referenced.  if uplo = 'l', the
//     **          leading n-by-n lower triangular part of a contains the lower
//     **          triangular part of the matrix a, and the strictly upper
//     **          triangular part of a is not referenced.
//     **
//     **          on exit, the block diagonal matrix d and the multipliers used
//     **          to obtain the factor u or l (see below for further details).
//     **
//     **  lda     (input) long int
//     **          the leading dimension of the array a.  lda >= max(1,n).
//     **
//     **  ipiv    (output) long int array, dimension (n)
//     **          details of the interchanges and the block structure of d.
//     **          if ipiv(k) > 0, then rows and columns k and ipiv(k) were
//     **          interchanged and d(k,k) is a 1-by-1 diagonal block.
//     **          if uplo = 'u' and ipiv(k) = ipiv(k-1) < 0, then rows and
//     **          columns k-1 and -ipiv(k) were interchanged and d(k-1:k,k-1:k)
//     **          is a 2-by-2 diagonal block.  if uplo = 'l' and ipiv(k) =
//     **          ipiv(k+1) < 0, then rows and columns k+1 and -ipiv(k) were
//     **          interchanged and d(k:k+1,k:k+1) is a 2-by-2 diagonal block.
//     **
//     **
//     **
//     **  info    (output) long int
//     **          = 0:  successful exit
//     **          < 0:  if info = -i, the i-th argument had an illegal value
//     **          > 0:  if info = i, d(i,i) is exactly zero.  the factorization
//     **                has been completed, but the block diagonal matrix d is
//     **                exactly singular, and division by zero will occur if it
//     **                is used to solve a system of equations.
//     **
//     **  further details
//     **  ===============
//     **
//     **  if uplo = 'u', then a = u*d*u', where
//     **     u = p(n)*u(n)* ... *p(k)u(k)* ...,
//     **  i.e., u is a product of terms p(k)*u(k), where k decreases from n to
//     **  1 in steps of 1 or 2, and d is a block diagonal matrix with 1-by-1
//     **  and 2-by-2 diagonal blocks d(k).  p(k) is a permutation matrix as
//     **  defined by ipiv(k), and u(k) is a unit upper triangular matrix, such
//     **  that if the diagonal block d(k) is of order s (s = 1 or 2), then
//     **
//     **             (   i    v    0   )   k-s
//     **     u(k) =  (   0    i    0   )   s
//     **             (   0    0    i   )   n-k
//     **                k-s   s   n-k
//     **
//     **  if s = 1, d(k) overwrites a(k,k), and v overwrites a(1:k-1,k).
//     **  if s = 2, the upper triangle of d(k) overwrites a(k-1,k-1), a(k-1,k),
//     **  and a(k,k), and v overwrites a(1:k-2,k-1:k).
//     **
//     **  if uplo = 'l', then a = l*d*l', where
//     **     l = p(1)*l(1)* ... *p(k)*l(k)* ...,
//     **  i.e., l is a product of terms p(k)*l(k), where k increases from 1 to
//     **  n in steps of 1 or 2, and d is a block diagonal matrix with 1-by-1
//     **  and 2-by-2 diagonal blocks d(k).  p(k) is a permutation matrix as
//     **  defined by ipiv(k), and l(k) is a unit lower triangular matrix, such
//     **  that if the diagonal block d(k) is of order s (s = 1 or 2), then
//     **
//     **             (   i    0     0   )  k-1
//     **     l(k) =  (   0    i     0   )  s
//     **             (   0    v     i   )  n-k-s+1
//     **                k-1   s  n-k-s+1
//     **
//     **  if s = 1, d(k) overwrites a(k,k), and v overwrites a(k+1:n,k).
//     **  if s = 2, the lower triangle of d(k) overwrites a(k,k), a(k+1,k),
//     **  and a(k+1,k+1), and v overwrites a(k+2:n,k:k+1).
//     **


namespace nt2 { namespace details
{
  extern "C"
  {
  void NT2_F77NAME(chetrf)(const char* uplo, const nt2_la_int* n, nt2_la_complex* a,
                       const nt2_la_int* lda, nt2_la_int* ipiv, nt2_la_complex* work,
                       const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(zhetrf)(const char* uplo, const nt2_la_int* n, nt2_la_complex* a,
                       const nt2_la_int* lda, nt2_la_int* ipiv, nt2_la_complex* work,
                       const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(ssytrf)(const char* uplo, const nt2_la_int* n, float* a,
                       const nt2_la_int* lda, nt2_la_int* ipiv,          float* work,
                       const nt2_la_int* lwork, nt2_la_int* info);
  void NT2_F77NAME(dsytrf)(const char* uplo, const nt2_la_int* n, double* a,
                       const nt2_la_int* lda, nt2_la_int* ipiv,         double* work,
                       const nt2_la_int* lwork, nt2_la_int* info);
  }

#define NT2_HETRF(NAME, T, TBASE)               \
  inline void hstrf(                            \
    const char* uplo,                           \
    const nt2_la_int* n,                        \
    T* a,                                       \
    const nt2_la_int* lda,                      \
    nt2_la_int* ipiv,                           \
    nt2_la_int* info,                           \
    workspace<T> & w)                           \
  {                                             \
    NT2_F77NAME( NAME )(uplo, n, a, lda, ipiv,  \
                        w.main(), query(),      \
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(uplo, n, a, lda,ipiv,   \
                        w.main(), &wn,          \
                        info);                  \
  }                                             \
    inline void hetrf(                          \
      const char* uplo,                         \
      const nt2_la_int* n,                      \
      T* a,                                     \
      const nt2_la_int* lda,                    \
      nt2_la_int* ipiv,                         \
      nt2_la_int* info)                         \
    {                                           \
      workspace<T> w;                           \
      hstrf(uplo, n, a, lda, ipiv, info, w);    \
    }                                           \
/**/

  NT2_HETRF(chetrf, std::complex<float>,  float)
    NT2_HETRF(zhetrf, std::complex<double>, double)

#undef NT2_HETRF


#define NT2_SYTRF(NAME, T)                      \
   inline void hstrf(                           \
     const char* uplo,                          \
     const nt2_la_int* n,                       \
     T* a,                                      \
     const nt2_la_int* lda,                     \
     nt2_la_int* ipiv,                          \
     nt2_la_int* info,                          \
     workspace<T> & w)                          \
   {                                            \
     NT2_F77NAME( NAME )(uplo, n, a, lda, ipiv, \
                         w.main(), query(),     \
                         info);                 \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(uplo, n, a, lda, ipiv,  \
                        w.main(), &wn,          \
                        info);                  \
   }                                            \
   inline void sytrf(                           \
     const char* uplo,                          \
     const nt2_la_int* n,                       \
     T* a,                                      \
     const nt2_la_int* lda,                     \
     nt2_la_int* ipiv,                          \
     nt2_la_int* info)                          \
   {                                            \
     workspace<T> w;                            \
     hstrf(uplo, n, a, lda, ipiv, info, w);     \
   }                                            \
/**/

  NT2_SYTRF(ssytrf, float)
  NT2_SYTRF(dsytrf, double)

#undef NT2_SYTRF

} }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of hstrf.hpp
// /////////////////////////////////////////////////////////////////////////////
