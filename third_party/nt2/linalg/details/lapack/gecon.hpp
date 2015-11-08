//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GECON_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GECON_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

namespace nt2
{
  /*
    (excerpt adapted from xgecon.f file commentaries)

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
    **  xgecon estimates the reciprocal of the condition number of a general
    **  DATA TYPE matrix a, in either the 1-norm or the infinity-norm, using
    **  the lu factorization computed by cgetrf.
    **
    **  an estimate is obtained for norm(inv(a)), and the reciprocal of the
    **  condition number is computed as
    **     rcond = 1 / ( norm(a) * norm(inv(a)) ).
    **
    **  arguments
    **  =========
    **
    **  norm    (input) char
    **          specifies whether the 1-norm condition number or the
    **          infinity-norm condition number is required:
    **          = '1' or 'o':  1-norm;
    **          = 'i':         infinity-norm.
    **
    **  n       (input) long int
    **          the order of the matrix a.  n >= 0.
    **
    **  a       (input) DATA TYPE array, dimension (lda,n)
    **          the factors l and u from the factorization a = p*l*u
    **          as computed by cgetrf.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,n).
    **
    **  anorm   (input) BASE DATA TYPE
    **          if norm = '1' or 'o', the 1-norm of the original matrix a.
    **          if norm = 'i', the infinity-norm of the original matrix a.
    **
    **  rcond   (output) BASE DATA TYPE
    **          the reciprocal of the condition number of the matrix a,
    **          computed as rcond = 1/(norm(a) * norm(inv(a))).
    **
    **
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value
    **
    **/
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgecon)(const char* norm, const nt2_la_int* n, const nt2_la_complex* a,
                               const nt2_la_int* lda, const float* anorm, float* rcond,
                               nt2_la_complex* work, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgecon)(const char* norm, const nt2_la_int* n, const double* a,
                           const nt2_la_int* lda, const double* anorm, double* rcond,
                           double* work, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(sgecon)(const char* norm, const nt2_la_int* n, const float* a,
                           const nt2_la_int* lda, const float* anorm, float* rcond,
                           float* work, nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(zgecon)(const char* norm, const nt2_la_int* n, const nt2_la_complex* a,
                           const nt2_la_int* lda, const double* anorm, double* rcond,
                           nt2_la_complex* work, double* rwork, nt2_la_int* info);
    }

#define NT2_GECON(NAME, T)                      \
    inline void gecon(const char* norm,         \
                      const nt2_la_int* n,      \
                      const T* a,               \
                      const nt2_la_int* lda,    \
                      const T* anorm,           \
                      T* rcond,                 \
                      nt2_la_int* info,         \
                      workspace<T> & w)         \
    {                                           \
      w.resize_integers(*n);                           \
      w.resize_main(4**n);                          \
      NT2_F77NAME( NAME )(norm, n, a, lda, anorm,                   \
                          rcond, w.main(), w.integers(), info);        \
    }                                                               \
    inline void gecon(const char* norm,                             \
                      const nt2_la_int* n,                          \
                      const T* a,                                   \
                      const nt2_la_int* lda,                        \
                      const T* anorm,                               \
                      T* rcond,                                     \
                      nt2_la_int* info)                             \
    {                                                               \
      workspace<T> w;                                               \
      gecon(norm, n, a, lda, anorm, rcond, info, w);                \
    }                                                               \

    NT2_GECON(sgecon, float)
    NT2_GECON(dgecon, double)

#undef NT2_GECON
#define NT2_GECON(NAME, T, TBASE)               \
    inline void gecon(const char* norm,         \
                      const nt2_la_int* n,      \
                      const T* a,               \
                      const nt2_la_int* lda,    \
                      const TBASE* anorm,       \
                      TBASE* rcond,             \
                      nt2_la_int* info,         \
                      workspace<T> & w)         \
    {                                           \
      w.resize_reals(2**n);                     \
      w.resize_main(2**n);                      \
      NT2_F77NAME( NAME )(norm, n, a, lda, anorm,                   \
                          rcond, w.main(), w.reals(), info);        \
    }                                                               \
    inline void gecon(const char* norm,                             \
                      const nt2_la_int* n,                          \
                      const T* a,                                   \
                      const nt2_la_int* lda,                        \
                      const TBASE* anorm,                           \
                      TBASE* rcond,                                 \
                      nt2_la_int* info)                             \
    {                                                               \
      workspace<T> w;                                               \
      gecon(norm, n, a, lda, anorm, rcond, info, w);                \
    }                                                               \

    NT2_GECON(cgecon, std::complex<float>, float)
    NT2_GECON(zgecon, std::complex<double>, double)

#undef NT2_GECON
      }
}
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of gecon.hpp
// /////////////////////////////////////////////////////////////////////////////
