//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GESVX_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GESVX_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
/*! \file gesvx_itf.hh
    (excerpt adapted from xgesvx.f file commentaries)

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
    **  xgesvx uses the lu factorization to compute the solution to a DATA TYPE
    **  system of linear equations
    **     a * x = b,
    **  where a is an n-by-n matrix and x and b are n-by-nrhs matrices.
    **
    **  error bounds on the solution and a condition estimate are also
    **  provided.
    **
    **  description
    **  ===========
    **
    **  the following steps are performed:
    **
    **  1. if fact = 'e', BASE DATA TYPE scaling factors are computed to equilibrate
    **     the system:
    **        trans = 'n':  diag(r)*a*diag(c)     *inv(ziag(c))*x = diag(r)*b
    **        trans = 't': (diag(r)*a*diag(c))**t *inv(diag(r))*x = diag(c)*b
    **        trans = 'c': (diag(r)*a*diag(c))**h *inv(diag(r))*x = diag(c)*b
    **     whether or not the system will be equilibrated depends on the
    **     scaling of the matrix a, but if equilibration is used, a is
    **     overwritten by diag(r)*a*diag(c) and b by diag(r)*b (if trans='n')
    **     or diag(c)*b (if trans = 't' or 'c').
    **
    **  2. if fact = 'n' or 'e', the lu decomposition is used to factor the
    **     matrix a (after equilibration if fact = 'e') as
    **        a = p * l * u,
    **     where p is a permutation matrix, l is a unit lower triangular
    **     matrix, and u is upper triangular.
    **
    **  3. if some u(i,i)=0, so that u is exactly singular, then the routine
    **     returns with info = i. otherwise, the factored form of a is used
    **     to estimate the condition number of the matrix a.  if the
    **     reciprocal of the condition number is less than machine precision,
    **     info = n+1 is returned as a warning, but the routine still goes on
    **     to solve for x and compute error bounds as described below.
    **
    **  4. the system of equations is solved for x using the factored form
    **     of a.
    **
    **  5. iterative refinement is applied to improve the computed solution
    **     matrix and calculate error bounds and backward error estimates
    **     for it.
    **
    **  6. if equilibration was used, the matrix x is premultiplied by
    **     diag(c) (if trans = 'n') or diag(r) (if trans = 't' or 'c') so
    **     that it solves the original system before equilibration.
    **
    **  arguments
    **  =========
    **
    **  fact    (input) char
    **          specifies whether or not the factored form of the matrix a is
    **          supplied on entry, and if not, whether the matrix a should be
    **          equilibrated before it is factored.
    **          = 'f':  on entry, af and ipiv contain the factored form of a.
    **                  if equed is not 'n', the matrix a has been
    **                  equilibrated with scaling factors given by r and c.
    **                  a, af, and ipiv are not modified.
    **          = 'n':  the matrix a will be copied to af and factored.
    **          = 'e':  the matrix a will be equilibrated if necessary, then
    **                  copied to af and factored.
    **
    **  trans   (input) char
    **          specifies the form of the system of equations:
    **          = 'n':  a * x = b     (no transpose)
    **          = 't':  a**t * x = b  (transpose)
    **          = 'c':  a**h * x = b  (conjugate transpose)
    **
    **  n       (input) long int
    **          the number of linear equations, i.e., the order of the
    **          matrix a.  n >= 0.
    **
    **  nrhs    (input) long int
    **          the number of right hand sides, i.e., the number of columns
    **          of the matrices b and x.  nrhs >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the n-by-n matrix a.  if fact = 'f' and equed is
    **          not 'n', then a must have been equilibrated by the scaling
    **          factors in r and/or c.  a is not modified if fact = 'f' or
    **          'n', or if fact = 'e' and equed = 'n' on exit.
    **
    **          on exit, if equed .ne. 'n', a is scaled as follows:
    **          equed = 'r':  a := diag(r) * a
    **          equed = 'c':  a := a * diag(c)
    **          equed = 'b':  a := diag(r) * a * diag(c).
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,n).
    **
    **  af      (input or output) DATA TYPE array, dimension (ldaf,n)
    **          if fact = 'f', then af is an input argument and on entry
    **          contains the factors l and u from the factorization
    **          a = p*l*u as computed by cgetrf.  if equed .ne. 'n', then
    **          af is the factored form of the equilibrated matrix a.
    **
    **          if fact = 'n', then af is an output argument and on exit
    **          returns the factors l and u from the factorization a = p*l*u
    **          of the original matrix a.
    **
    **          if fact = 'e', then af is an output argument and on exit
    **          returns the factors l and u from the factorization a = p*l*u
    **          of the equilibrated matrix a (see the description of a for
    **          the form of the equilibrated matrix).
    **
    **  ldaf    (input) long int
    **          the leading dimension of the array af.  ldaf >= max(1,n).
    **
    **  ipiv    (input or output) long int array, dimension (n)
    **          if fact = 'f', then ipiv is an input argument and on entry
    **          contains the pivot indices from the factorization a = p*l*u
    **          as computed by cgetrf; row i of the matrix was interchanged
    **          with row ipiv(i).
    **
    **          if fact = 'n', then ipiv is an output argument and on exit
    **          contains the pivot indices from the factorization a = p*l*u
    **          of the original matrix a.
    **
    **          if fact = 'e', then ipiv is an output argument and on exit
    **          contains the pivot indices from the factorization a = p*l*u
    **          of the equilibrated matrix a.
    **
    **  equed   (input or output) char
    **          specifies the form of equilibration that was done.
    **          = 'n':  no equilibration (always true if fact = 'n').
    **          = 'r':  row equilibration, i.e., a has been premultiplied by
    **                  diag(r).
    **          = 'c':  column equilibration, i.e., a has been postmultiplied
    **                  by diag(c).
    **          = 'b':  both row and column equilibration, i.e., a has been
    **                  replaced by diag(r) * a * diag(c).
    **          equed is an input argument if fact = 'f'; otherwise, it is an
    **          output argument.
    **
    **  r       (input or output) BASE DATA TYPE array, dimension (n)
    **          the row scale factors for a.  if equed = 'r' or 'b', a is
    **          multiplied on the left by diag(r); if equed = 'n' or 'c', r
    **          is not accessed.  r is an input argument if fact = 'f';
    **          otherwise, r is an output argument.  if fact = 'f' and
    **          equed = 'r' or 'b', each element of r must be positive.
    **
    **  c       (input or output) BASE DATA TYPE array, dimension (n)
    **          the column scale factors for a.  if equed = 'c' or 'b', a is
    **          multiplied on the right by diag(c); if equed = 'n' or 'r', c
    **          is not accessed.  c is an input argument if fact = 'f';
    **          otherwise, c is an output argument.  if fact = 'f' and
    **          equed = 'c' or 'b', each element of c must be positive.
    **
    **  b       (input/output) DATA TYPE array, dimension (ldb,nrhs)
    **          on entry, the n-by-nrhs right hand side matrix b.
    **          on exit,
    **          if equed = 'n', b is not modified;
    **          if trans = 'n' and equed = 'r' or 'b', b is overwritten by
    **          diag(r)*b;
    **          if trans = 't' or 'c' and equed = 'c' or 'b', b is
    **          overwritten by diag(c)*b.
    **
    **  ldb     (input) long int
    **          the leading dimension of the array b.  ldb >= max(1,n).
    **
    **  x       (output) DATA TYPE array, dimension (ldx,nrhs)
    **          if info = 0 or info = n+1, the n-by-nrhs solution matrix x
    **          to the original system of equations.  note that a and b are
    **          modified on exit if equed .ne. 'n', and the solution to the
    **          equilibrated system is inv(diag(c))*x if trans = 'n' and
    **          equed = 'c' or 'b', or inv(diag(r))*x if trans = 't' or 'c'
    **          and equed = 'r' or 'b'.
    **
    **  ldx     (input) long int
    **          the leading dimension of the array x.  ldx >= max(1,n).
    **
    **  rcond   (output) BASE DATA TYPE
    **          the estimate of the reciprocal condition number of the matrix
    **          a after equilibration (if done).  if rcond is less than the
    **          machine precision (in particular, if rcond = 0), the matrix
    **          is singular to WORKing precision.  this condition is
    **          indicated by a return code of info > 0.
    **
    **  ferr    (output) BASE DATA TYPE array, dimension (nrhs)
    **          the estimated forward error bound for each solution vector
    **          x(j) (the j-th column of the solution matrix x).
    **          if xtrue is the true solution corresponding to x(j), ferr(j)
    **          is an estimated upper bound for the magnitude of the largest
    **          element in (x(j) - xtrue) divided by the magnitude of the
    **          largest element in x(j).  the estimate is as reliable as
    **          the estimate for rcond, and is almost always a slight
    **          overestimate of the true error.
    **
    **  berr    (output) BASE DATA TYPE array, dimension (nrhs)
    **          the componentwise relative backward error of each solution
    **          vector x(j) (i.e., the smallest relative change in
    **          any element of a or b that makes x(j) an exact solution).
    **
    **
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value
    **          > 0:  if info = i, and i is
    **                <= n:  u(i,i) is exactly zero.  the factorization has
    **                       been completed, but the factor u is exactly
    **                       singular, so the solution and error bounds
    **                       could not be computed. rcond = 0 is returned.
    **                = n+1: u is nonsingular, but rcond is less than machine
    **                       precision, meaning that the matrix is singular
    **                       to WORKing precision.  nevertheless, the
    **                       solution and error bounds are computed because
    **                       there are a number of situations where the
    **                       computed solution can be more accurate than the
    **                       value of rcond would suggest.
    **
**/
namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const float* r, const float* c, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_complex* x, const nt2_la_int* ldx, float* rcond, float* ferr, float* berr, nt2_la_complex* work,
                               float* rwork, nt2_la_int* info);
      void NT2_F77NAME(dgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const double* a, const nt2_la_int* lda, double* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const double* r, const double* c, double* b, const nt2_la_int* ldb,
                               double* x, const nt2_la_int* ldx, double* rcond, double* ferr, double* berr, double* work,
                               nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(sgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const float* a, const nt2_la_int* lda, float* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const float* r, const float* c, float* b, const nt2_la_int* ldb,
                               float* x, const nt2_la_int* ldx, float* rcond, float* ferr, float* berr, float* work,
                               nt2_la_int* iwork, nt2_la_int* info);
      void NT2_F77NAME(zgesvx)(const char* fact, const char* trans, const nt2_la_int* n, const nt2_la_int* nrhs,
                               const nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* af, const nt2_la_int* ldaf, nt2_la_int* ipiv,
                               char* equed, const double* r, const double* c, nt2_la_complex* b, const nt2_la_int* ldb,
                               nt2_la_complex* x, const nt2_la_int* ldx, double* rcond, double* ferr, double* berr, nt2_la_complex* work,
                               double* rwork, nt2_la_int* info);
    }

#define NT2_GESVX(NAME, T)                                        \
    inline void gesvx(const char* fact,                           \
                      const char* trans,                          \
                      const nt2_la_int* n,                        \
                      const nt2_la_int* nrhs,                     \
                      const T* a,                                 \
                      const nt2_la_int* lda,                      \
                      T* af,                                      \
                      const nt2_la_int* ldaf,                     \
                      nt2_la_int* ipiv,                           \
                      char* equed,                                \
                      const T* r,                                 \
                      const T* c,                                 \
                      T* b,                                       \
                      const nt2_la_int* ldb,                      \
                      T* x,                                       \
                      const nt2_la_int* ldx,                      \
                      T* rcond,                                   \
                      T* ferr,                                    \
                      T* berr,                                    \
                      nt2_la_int* info,                           \
                      workspace<T> & w)                           \
    {                                                             \
      w.resize_integers(*n);                                      \
      w.resize_main(4**n);                                        \
      NT2_F77NAME( NAME )(fact, trans, n, nrhs, a, lda, af, ldaf, \
                          ipiv, equed, r, c, b, ldb, x, ldx,      \
                          rcond, ferr, berr, w.main(),            \
                          w.integers(), info);                    \
    }                                                             \
    inline void gesvx(const char* fact,                           \
                      const char* trans,                          \
                      const nt2_la_int* n,                        \
                      const nt2_la_int* nrhs,                     \
                      const T* a,                                 \
                      const nt2_la_int* lda,                      \
                      T* af,                                      \
                      const nt2_la_int* ldaf,                     \
                      nt2_la_int* ipiv,                           \
                      char* equed,                                \
                      const T* r,                                 \
                      const T* c,                                 \
                      T* b,                                       \
                      const nt2_la_int* ldb,                      \
                      T* x,                                       \
                      const nt2_la_int* ldx,                      \
                      T* rcond,                                   \
                      T* ferr,                                    \
                      T* berr,                                    \
                      nt2_la_int* info)                           \
    {                                                             \
      workspace<T> w;                                             \
      gesvx(fact, trans, n, nrhs, a, lda, af, ldaf, ipiv,         \
            equed, r, c, b, ldb, x, ldx,                          \
            rcond, ferr, berr, info, w);                          \
    }                                                             \

    NT2_GESVX(sgesvx, float)
    NT2_GESVX(dgesvx, double)
#undef NT2_GESVX

#define NT2_GESVX(NAME, T, TBASE)                                 \
    inline void gesvx(const char* fact,                           \
                      const char* trans,                          \
                      const nt2_la_int* n,                        \
                      const nt2_la_int* nrhs,                     \
                      const T* a,                                 \
                      const nt2_la_int* lda,                      \
                      T* af,                                      \
                      const nt2_la_int* ldaf,                     \
                      nt2_la_int* ipiv,                           \
                      char* equed,                                \
                      const TBASE* r,                             \
                      const TBASE* c,                             \
                      T* b,                                       \
                      const nt2_la_int* ldb,                      \
                      T* x,                                       \
                      const nt2_la_int* ldx,                      \
                      TBASE* rcond,                               \
                      TBASE* ferr,                                \
                      TBASE* berr,                                \
                      nt2_la_int* info,                           \
                      workspace<T> & w)                           \
    {                                                             \
      w.resize_reals(2**n);                                       \
      w.resize_main(2**n);                                        \
      NT2_F77NAME( NAME )(fact, trans, n, nrhs, a, lda, af, ldaf, \
                          ipiv, equed, r, c, b, ldb, x, ldx,      \
                          rcond, ferr, berr, w.main(),            \
                          w.reals(), info);                       \
    }                                                             \
    inline void gesvx(const char* fact,                           \
                      const char* trans,                          \
                      const nt2_la_int* n,                        \
                      const nt2_la_int* nrhs,                     \
                      const T* a,                                 \
                      const nt2_la_int* lda,                      \
                      T* af,                                      \
                      const nt2_la_int* ldaf,                     \
                      nt2_la_int* ipiv,                           \
                      char* equed,                                \
                      const TBASE* r,                             \
                      const TBASE* c,                             \
                      T* b,                                       \
                      const nt2_la_int* ldb,                      \
                      T* x,                                       \
                      const nt2_la_int* ldx,                      \
                      TBASE* rcond,                               \
                      TBASE* ferr,                                \
                      TBASE* berr,                                \
                      nt2_la_int* info)                           \
    {                                                             \
      workspace<T> w;                                             \
      gesvx(fact, trans, n, nrhs, a, lda, af, ldaf, ipiv,         \
            equed, r, c, b, ldb, x, ldx,                          \
            rcond, ferr, berr, info, w);                          \
    }                                                             \


    NT2_GESVX(cgesvx, std::complex<float>,  float)
    NT2_GESVX(zgesvx, std::complex<double>, double)

#undef NT2_GESVX
  }
}

#endif

