//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GESVD_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GESVD_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

namespace nt2
{
  namespace details
  {
    /**  purpose
     **  =======
     **
     **  xgesvd computes the singular value decomposition (svd) of a DATA TYPE
     **  m-by-n matrix a, optionally computing the left and/or right singular
     **  vectors. the svd is written
     **
     **       a = u * sigma * conjugate-transpose(v)
     **
     **  where sigma is an m-by-n matrix which is zero except for its
     **  min(m,n) diagonal elements, u is an m-by-m unitary matrix, and
     **  v is an n-by-n unitary matrix.  the diagonal elements of sigma
     **  are the singular values of a; they are BASE DATA TYPE and non-negative, and
     **  are returned in descending order.  the first min(m,n) columns of
     **  u and v are the left and right singular vectors of a.
     **
     **  note that the routine returns v**h, not v.
     **
     **  arguments
     **  =========
     **
     **  jobu    (input) char
     **          specifies options for computing all or part of the matrix u:
     **          = 'a':  all m columns of u are returned in array u:
     **          = 's':  the first min(m,n) columns of u (the left singular
     **                  vectors) are returned in the array u;
     **          = 'o':  the first min(m,n) columns of u (the left singular
     **                  vectors) are overwritten on the array a;
     **          = 'n':  no columns of u (no left singular vectors) are
     **                  computed.
     **
     **  jobvt   (input) char
     **          specifies options for computing all or part of the matrix
     **          v**h:
     **          = 'a':  all n rows of v**h are returned in the array vt;
     **          = 's':  the first min(m,n) rows of v**h (the right singular
     **                  vectors) are returned in the array vt;
     **          = 'o':  the first min(m,n) rows of v**h (the right singular
     **                  vectors) are overwritten on the array a;
     **          = 'n':  no rows of v**h (no right singular vectors) are
     **                  computed.
     **
     **          jobvt and jobu cannot both be 'o'.
     **
     **  m       (input) nt2_la_int
     **          the number of rows of the input matrix a.  m >= 0.
     **
     **  n       (input) nt2_la_int
     **          the number of columns of the input matrix a.  n >= 0.
     **
     **  a       (input/output) DATA TYPE array, dimension (lda,n)
     **          on entry, the m-by-n matrix a.
     **          on exit,
     **          if jobu = 'o',  a is overwritten with the first min(m,n)
     **                          columns of u (the left singular vectors,
     **                          stored columnwise);
     **          if jobvt = 'o', a is overwritten with the first min(m,n)
     **                          rows of v**h (the right singular vectors,
     **                          stored rowwise);
     **          if jobu .ne. 'o' and jobvt .ne. 'o', the contents of a
     **                          are destroyed.
     **
     **  lda     (input) nt2_la_int
     **          the leading dimension of the array a.  lda >= max(1,m).
     **
     **  s       (output) BASE DATA TYPE array, dimension (min(m,n))
     **          the singular values of a, sorted so that s(i) >= s(i+1).
     **
     **  u       (output) DATA TYPE array, dimension (ldu,ucol)
     **          (ldu,m) if jobu = 'a' or (ldu,min(m,n)) if jobu = 's'.
     **          if jobu = 'a', u contains the m-by-m unitary matrix u;
     **          if jobu = 's', u contains the first min(m,n) columns of u
     **          (the left singular vectors, stored columnwise);
     **          if jobu = 'n' or 'o', u is not referenced.
     **
     **  ldu     (input) nt2_la_int
     **          the leading dimension of the array u.  ldu >= 1; if
     **          jobu = 's' or 'a', ldu >= m.
     **
     **  vt      (output) DATA TYPE array, dimension (ldvt,n)
     **          if jobvt = 'a', vt contains the n-by-n unitary matrix
     **          v**h;
     **          if jobvt = 's', vt contains the first min(m,n) rows of
     **          v**h (the right singular vectors, stored rowwise);
     **          if jobvt = 'n' or 'o', vt is not referenced.
     **
     **  ldvt    (input) nt2_la_int
     **          the leading dimension of the array vt.  ldvt >= 1; if
     **          jobvt = 'a', ldvt >= n; if jobvt = 's', ldvt >= min(m,n).
     **
     **
     **
     **
     **  info    (output) nt2_la_int
     **          = 0:  successful exit.
     **          < 0:  if info = -i, the i-th argument had an illegal value.
     **          > 0:  if cbdsqr did not converge, info specifies how many
     **                superdiagonals of an intermediate bidiagonal form b
     **                did not converge to zero. see the description of RWORK
     **                above for details.
     **
     **/
    extern "C"
    {
      void NT2_F77NAME(cgesvd)(const char* jobu, const char* jobvt, const nt2_la_int* m, const nt2_la_int* n,
                           nt2_la_complex* a, const nt2_la_int* lda, float* s, const nt2_la_complex* u, const nt2_la_int* ldu,
                           const nt2_la_complex* vt, const nt2_la_int* ldvt,
                           nt2_la_complex* work, const nt2_la_int* lwork, float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgesvd)(const char* jobu, const char* jobvt, const nt2_la_int* m, const nt2_la_int* n,
                           double* a, const nt2_la_int* lda, double* s, const double* u, const nt2_la_int* ldu,
                           const double* vt, const nt2_la_int* ldvt,
                           double* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(sgesvd)(const char* jobu, const char* jobvt, const nt2_la_int* m, const nt2_la_int* n,
                           float* a, const nt2_la_int* lda, float* s, const float* u, const nt2_la_int* ldu,
                           const float* vt, const nt2_la_int* ldvt,
                           float* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(zgesvd)(const char* jobu, const char* jobvt, const nt2_la_int* m, const nt2_la_int* n,
                           nt2_la_complex* a, const nt2_la_int* lda, double* s, const nt2_la_complex* u, const nt2_la_int* ldu,
                           const nt2_la_complex* vt, const nt2_la_int* ldvt,
                           nt2_la_complex* work, const nt2_la_int* lwork, double* rwork, nt2_la_int* info);
    }

#define NT2_GESVD(NAME, T, TBASE)                                       \
    inline void gesvd(const char* jobu,                                 \
                      const char* jobvt,                                \
                      const nt2_la_int* m,                              \
                      const nt2_la_int* n,                              \
                      T* a,                                             \
                      const nt2_la_int* lda,                            \
                      TBASE* s,                                         \
                      const T* u,                                       \
                      const nt2_la_int* ldu,                            \
                      const T* vt,                                      \
                      const nt2_la_int* ldvt,                           \
                      nt2_la_int* info,                                 \
                      nt2::details::workspace<T> & w)                   \
    {                                                                   \
      w.resize_reals(5*nt2::min(*m,*n));                                \
      NT2_F77NAME( NAME )(jobu, jobvt, m, n, a, lda, s, u, ldu,         \
                          vt, ldvt, w.main(), query(), w.reals(), info);\
      nt2_la_int wn = 5*nt2::max(m, n);                                 \
      w.resize_main(wn);                                                \
      NT2_F77NAME( NAME )(jobu, jobvt, m, n, a, lda, s, u, ldu,         \
                      vt,ldvt,w.main(),&wn,w.reals(),info);             \
    }                                                                   \
    inline void gesvd(const char* jobu,                                 \
                      const char* jobvt,                                \
                      const nt2_la_int* m,                              \
                      const nt2_la_int* n,                              \
                      T* a,                                             \
                      const nt2_la_int* lda,                            \
                      TBASE* s,                                         \
                      const T* u,                                       \
                      const nt2_la_int* ldu,                            \
                      const T* vt,                                      \
                      const nt2_la_int* ldvt,                           \
                      nt2_la_int* info)                                 \
    {                                                                   \
      nt2::details::workspace<T> w;                                     \
      gesvd(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, info, w);   \
    }                                                                   \

    NT2_GESVD(cgesvd, std::complex<float>,  float)
    NT2_GESVD(zgesvd, std::complex<double>, double)
#undef NT2_GESVD

#define NT2_GESVD(NAME, T)                                              \
    inline void gesvd(const char* jobu,                                 \
                      const char* jobvt,                                \
                      const nt2_la_int* m,                              \
                      const nt2_la_int* n,                              \
                      T* a,                                             \
                      const nt2_la_int* lda,                            \
                      T* s,                                             \
                      const T* u,                                       \
                      const nt2_la_int* ldu,                            \
                      const T* vt,                                      \
                      const nt2_la_int* ldvt,                           \
                      nt2_la_int* info,                                 \
                      nt2::details::workspace<T> & w)                   \
    {                                                                   \
      NT2_F77NAME( NAME )(jobu, jobvt, m, n, a, lda, s, u, ldu,         \
                          vt, ldvt, w.main(), query(), info);           \
      nt2_la_int wn = 5*nt2::max(m, n);                                 \
      w.resize_main(wn);                                                \
      NT2_F77NAME( NAME )(jobu, jobvt, m, n, a, lda, s, u, ldu,         \
                          vt,ldvt,w.main(),&wn,info);                   \
    }                                                                   \
    inline void gesvd(const char* jobu,                                 \
                      const char* jobvt,                                \
                      const nt2_la_int* m,                              \
                      const nt2_la_int* n,                              \
                      T* a,                                             \
                      const nt2_la_int* lda,                            \
                      T* s,                                             \
                      const T* u,                                       \
                      const nt2_la_int* ldu,                            \
                      const T* vt,                                      \
                      const nt2_la_int* ldvt,                           \
                      nt2_la_int* info)                                 \
    {                                                                   \
      nt2::details::workspace<T> w;                                     \
      gesvd(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, info, w);   \
    }                                                                   \

    NT2_GESVD(sgesvd, float)
    NT2_GESVD(dgesvd, double)
#undef NT2_GESVD

  }
}


#endif

