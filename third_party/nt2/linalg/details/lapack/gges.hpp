//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GGES_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GGES_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>


/*! \file gges_itf.hh
    (excerpt adapted from xgges.f file commentaries)

    DATA TYPE can mean float, double, std::complex<float>, std::complex<double>

    BASE TYPE can mean respectively float, double, float, double

    In some cases only two of these types are available
    the two real or the two std::complex ones.
    CAPITALIZED PARAMETERS are FORTRAN parameters who are not used directly
    in the C++ calls, but through the workspace parameter,
    their use is transparent for the caller

    *
    **  purpose
    **  =======
    **
    **  xgges computes for a pair of n-by-n DATA TYPE nonsymmetric matrices
    **  (a,b), the generalized eigenvalues, the generalized DATA TYPE schur
    **  form (s, t), and optionally left and/or right schur vectors (vsl
    **  and vsr). this gives the generalized schur factorization
    **
    **          (a,b) = ( (vsl)*s*(vsr)**h, (vsl)*t*(vsr)**h )
    **
    **  where (vsr)**h is the conjugate-transpose of vsr.
    **
    **  optionally, it also orders the eigenvalues so that a selected cluster
    **  of eigenvalues appears in the leading diagonal blocks of the upper
    **  triangular matrix s and the upper triangular matrix t. the leading
    **  columns of vsl and vsr then form an unitary basis for the
    **  corresponding left and right eigenspaces (zeflating subspaces).
    **
    **  (if only the generalized eigenvalues are needed, use the driver
    **  cggev instead, which is faster.)
    **
    **  a generalized eigenvalue for a pair of matrices (a,b) is a scalar w
    **  or a ratio alpha/beta = ws, such that  a - w*b is singular.  it is
    **  usually represented as the pair (alpha,beta), as there is a
    **  reasonable interpretation for beta=0, and even for both being zero.
    **
    **  a pair of matrices (s,t) is in generalized DATA TYPE schur form if s
    **  and t are upper triangular and, in addition, the diagonal elements
    **  of t are non-negative BASE DATA TYPE numbers.
    **
    **  arguments
    **  =========
    **
    **  jobvsl  (input) char
    **          = 'n':  do not compute the left  vectors;
    **          = 'v':  compute the left schur vectors.
    **
    **  jobvsr  (input) char
    **          = 'n':  do not compute the right  vectors;
    **          = 'v':  compute the right schur vectors.
    **
    **  sort    (input) char
    **          specifies whether or not to order the eigenvalues on the
    **          diagonal of the generalized schur form.
    **          = 'n':  eigenvalues are not ordered;
    **          = 's':  eigenvalues are ordered (see selctg).
    **
    **  selctg  (input) logical function of two DATA TYPE arguments
    **          selctg must be declared external in the calling subroutine.
    **          if sort = 'n', selctg is not referenced.
    **          if sort = 's', selctg is used to select eigenvalues to sort
    **          to the top left of the schur form.
    **          an eigenvalue alpha(j)/beta(j) is selected if
    **          selctg(alpha(j),beta(j)) is true.
    **
    **          note that a selected DATA TYPE eigenvalue may no longer satisfy
    **          selctg(alpha(j),beta(j)) = .true. after ordering, since
    **          ordering may change the value of DATA TYPE eigenvalues
    **          (especially if the eigenvalue is ill-conditioned), in this
    **          case info is set to n+2 (see info below).
    **
    **  n       (input) long int
    **          the order of the matrices a, b, vsl, and vsr.  n >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda, n)
    **          on entry, the first of the pair of matrices.
    **          on exit, a has been overwritten by its generalized schur
    **          form s.
    **
    **  lda     (input) long int
    **          the leading dimension of a.  lda >= max(1,n).
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb, n)
    **          on entry, the second of the pair of matrices.
    **          on exit, b has been overwritten by its generalized schur
    **          form t.
    **
    **  ldb     (input) long int
    **          the leading dimension of b.  ldb >= max(1,n).
    **
    **  sdim    (output) long int
    **          if sort = 'n', sdim = 0.
    **          if sort = 's', sdim = number of eigenvalues (after sorting)
    **          for which selctg is true.
    **
    **  alpha   (output) DATA TYPE array, dimension (n)
    **  beta    (output) DATA TYPE array, dimension (n)
    **          on exit,  alpha(j)/beta(j), j=1,...,n, will be the
    **          generalized eigenvalues.  alpha(j), j=1,...,n  and  beta(j),
    **          j=1,...,n  are the diagonals of the DATA TYPE schur form (a,b)
    **          output by xgges. the  beta(j) will be non-negative BASE DATA TYPE.
    **
    **          note: the quotients alpha(j)/beta(j) may easily over- or
    **          underflow, and beta(j) may even be zero.  thus, the user
    **          should avoid naively computing the ratio alpha/beta.
    **          however, alpha will be always less than and usually
    **          comparable with norm(a) in magnitude, and beta always less
    **          than and usually comparable with norm(b).
    **
    **  vsl     (output) DATA TYPE array, dimension (ldvsl,n)
    **          if jobvsl = 'v', vsl will contain the left schur vectors.
    **          not referenced if jobvsl = 'n'.
    **
    **  ldvsl   (input) long int
    **          the leading dimension of the matrix vsl. ldvsl >= 1, and
    **          if jobvsl = 'v', ldvsl >= n.
    **
    **  vsr     (output) DATA TYPE array, dimension (ldvsr,n)
    **          if jobvsr = 'v', vsr will contain the right schur vectors.
    **          not referenced if jobvsr = 'n'.
    **
    **  ldvsr   (input) long int
    **          the leading dimension of the matrix vsr. ldvsr >= 1, and
    **          if jobvsr = 'v', ldvsr >= n.
    **
    **
    **
    **
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value.
    **          =1,...,n:
    **                the qz iteration failed.  (a,b) are not in schur
    **                form, but alpha(j) and beta(j) should be correct for
    **                j=info+1,...,n.
    **          > n:  =n+1: other than qz iteration failed in chgeqz
    **                =n+2: after reordering, roundoff changed values of
    **                      some DATA TYPE eigenvalues so that leading
    **                      eigenvalues in the generalized schur form no
    **                      longer satisfy selctg=.true.  this could also
    **                      be caused due to scaling.
    **                =n+3: reordering falied in ctgsen.
    **
**/
namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgges)(const char* jobvsl, const char* jobvsr, const char* sort,
                          selectall_t* selctg, const nt2_la_int* n, nt2_la_complex* a,
                          const nt2_la_int* lda, const nt2_la_complex* b, const nt2_la_int* ldb,
                          nt2_la_int* sdim, nt2_la_complex* alpha, nt2_la_complex* beta,
                          const nt2_la_complex* vsl, const nt2_la_int* ldvsl, const nt2_la_complex* vsr,
                          const nt2_la_int* ldvsr, nt2_la_complex* work, const nt2_la_int* lwork,
                          float* rwork, nt2_la_int* bwork, nt2_la_int* info);
      void NT2_F77NAME(dgges)(const char* jobvsl, const char* jobvsr, const char* sort,
                          selectall2_t* delctg, const nt2_la_int* n, double* a,
                          const nt2_la_int* lda, const double* b, const nt2_la_int* ldb,
                          nt2_la_int* sdim, double* alphar, double* alphai, double* beta,
                          const double* vsl, const nt2_la_int* ldvsl, const double* vsr,
                          const nt2_la_int* ldvsr, double* work, const nt2_la_int* lwork,
                          nt2_la_int* bwork, nt2_la_int* info);
      void NT2_F77NAME(sgges)(const char* jobvsl, const char* jobvsr, const char* sort,
                          selectall2_t* selctg, const nt2_la_int* n, float* a,
                          const nt2_la_int* lda, const float* b, const nt2_la_int* ldb,
                          nt2_la_int* sdim, float* alphar, float* alphai, float* beta,
                          const float* vsl, const nt2_la_int* ldvsl, const float* vsr,
                          const nt2_la_int* ldvsr, float* work, const nt2_la_int* lwork,
                          nt2_la_int* bwork, nt2_la_int* info);
      void NT2_F77NAME(zgges)(const char* jobvsl, const char* jobvsr, const char* sort,
                          selectall_t* delctg, const nt2_la_int* n, nt2_la_complex* a,
                          const nt2_la_int* lda, const nt2_la_complex* b, const nt2_la_int* ldb,
                          nt2_la_int* sdim, nt2_la_complex* alpha, nt2_la_complex* beta,
                          const nt2_la_complex* vsl, const nt2_la_int* ldvsl, const nt2_la_complex* vsr,
                          const nt2_la_int* ldvsr, nt2_la_complex* work, const nt2_la_int* lwork,
                          double* rwork, nt2_la_int* bwork, nt2_la_int* info);
    }

#define NT2_GEES(NAME, T)                       \
  inline void gges(const char* jobvsl,          \
                   const char* jobvsr,          \
                   const char* sort,            \
                   selectall2_t* selctg,        \
                   const nt2_la_int* n,         \
                   T* a,                        \
                   const nt2_la_int* lda,       \
                   const T* b,                  \
                   const nt2_la_int* ldb,       \
                   nt2_la_int* sdim,            \
                   T* alphar,                   \
                   T* alphai,                   \
                   T* beta,                     \
                   const T* vsl,                \
                   const nt2_la_int* ldvsl,     \
                   const T* vsr,                \
                   const nt2_la_int* ldvsr,     \
                   nt2_la_int* info,            \
                   workspace<T> & w)            \
  {                                             \
    w.resize_logicals(*sort == 'N'?1:*n);       \
    NT2_F77NAME(NAME)(jobvsl, jobvsr, sort,     \
                      selctg, n, a, lda,        \
                      b, ldb, sdim, alphar,     \
                      alphai, beta, vsl, ldvsl, \
                      vsr, ldvsr, w.main(),     \
                      query(), w.logicals(),    \
                      info);                    \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME(NAME)(jobvsl, jobvsr, sort,     \
                      selctg, n, a, lda,        \
                      b, ldb, sdim, alphar,     \
                      alphai, beta, vsl, ldvsl, \
                      vsr, ldvsr, w.main(),     \
                      &wn, w.logicals(),        \
                      info);                    \
  }                                             \
  inline void gges(const char* jobvsl,          \
                   const char* jobvsr,          \
                   const char* sort,            \
                   selectall2_t* selctg,        \
                   const nt2_la_int* n,         \
                   T* a,                        \
                   const nt2_la_int* lda,       \
                   const T* b,                  \
                   const nt2_la_int* ldb,       \
                   nt2_la_int* sdim,            \
                   T* alphar,                   \
                   T* alphai,                   \
                   T* beta,                     \
                   const T* vsl,                \
                   const nt2_la_int* ldvsl,     \
                   const T* vsr,                \
                   const nt2_la_int* ldvsr,     \
                   nt2_la_int* info)            \
  {                                             \
    workspace<T> w;                             \
    gges(jobvsl, jobvsr, sort,                  \
         selctg, n, a, lda,                     \
         b, ldb, sdim, alphar,                  \
         alphai, beta, vsl, ldvsl,              \
         vsr, ldvsr, info, w);                  \
  }                                             \
        /**/

    NT2_GEES(sgges, float)
    NT2_GEES(dgges, double)

#undef NT2_GEES
#define NT2_GEES(NAME, T, TBASE)                \
  inline void gges(const char* jobvsl,          \
                   const char* jobvsr,          \
                   const char* sort,            \
                   selectall_t* delctg,         \
                   const nt2_la_int* n,         \
                   T* a,                        \
                   const nt2_la_int* lda,       \
                   const T* b,                  \
                   const nt2_la_int* ldb,       \
                   nt2_la_int* sdim,            \
                   T* alpha,                    \
                   T* beta,                     \
                   const T* vsl,                \
                   const nt2_la_int* ldvsl,     \
                   const T* vsr,                \
                   const nt2_la_int* ldvsr,     \
                   nt2_la_int* info,            \
                   workspace<T> & w)            \
  {                                             \
    w.resize_reals(8**n);                       \
    w.resize_logicals(*sort == 'N'?1:*n);       \
    NT2_F77NAME(NAME)(jobvsl, jobvsr, sort,     \
                      delctg, n, a, lda,        \
                      b, ldb, sdim, alpha,      \
                      beta, vsl, ldvsl, vsr,    \
                      ldvsr, w.main(), query(), \
                      w.reals(), w.logicals(),  \
                      info);                    \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME(NAME)(jobvsl, jobvsr, sort,     \
                      delctg, n, a, lda,        \
                      b, ldb, sdim, alpha,      \
                      beta, vsl, ldvsl, vsr,    \
                      ldvsr, w.main(),          \
                      &wn, w.reals(),           \
                      w.logicals(), info);      \
  }                                             \
  inline void gges(const char* jobvsl,          \
                   const char* jobvsr,          \
                   const char* sort,            \
                   selectall_t* delctg,         \
                   const nt2_la_int* n,         \
                   T* a,                        \
                   const nt2_la_int* lda,       \
                   const T* b,                  \
                   const nt2_la_int* ldb,       \
                   nt2_la_int* sdim,            \
                   T* alpha,                    \
                   T* beta,                     \
                   const T* vsl,                \
                   const nt2_la_int* ldvsl,     \
                   const T* vsr,                \
                   const nt2_la_int* ldvsr,     \
                   nt2_la_int* info)            \
  {                                             \
    workspace<T> w;                             \
    gges(jobvsl, jobvsr, sort,                  \
         delctg, n, a, lda,                     \
         b, ldb, sdim, alpha,                   \
         beta, vsl, ldvsl, vsr,                 \
         ldvsr, info, w);                       \
  }                                             \
          /**/

    NT2_GEES(cgges, std::complex<float>,  float)
    NT2_GEES(zgges, std::complex<double>, double)

#undef NT2_GEES


  }
}

#endif
