//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GEBAK_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GEBAK_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

/*! \file gebak_itf.hh
    (excerpt adapted from xgebak.f file commentaries)

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
    **  xgebak forms the right or left eigenvectors of a DATA TYPE general
    **  matrix by backward transformation on the computed eigenvectors of the
    **  balanced matrix output by cgebal.
    **
    **  arguments
    **  =========
    **
    **  job     (input) char
    **          specifies the type of backward transformation required:
    **          = 'n', do nothing, return immediately;
    **          = 'p', do backward transformation for permutation only;
    **          = 's', do backward transformation for scaling only;
    **          = 'b', do backward transformations for both permutation and
    **                 scaling.
    **          job must be the same as the argument job supplied to cgebal.
    **
    **  side    (input) char
    **          = 'r':  v contains right eigenvectors;
    **          = 'l':  v contains left eigenvectors.
    **
    **  n       (input) long int
    **          the number of rows of the matrix v.  n >= 0.
    **
    **  ilo     (input) long int
    **  ihi     (input) long int
    **          the integers ilo and ihi determined by cgebal.
    **          1 <= ilo <= ihi <= n, if n > 0; ilo=1 and ihi=0, if n=0.
    **
    **  scale   (input) BASE DATA TYPE array, dimension (n)
    **          details of the permutation and scaling factors, as returned
    **          by cgebal.
    **
    **  m       (input) long int
    **          the number of columns of the matrix v.  m >= 0.
    **
    **  v       (input/output) DATA TYPE array, dimension (ldv,m)
    **          on entry, the matrix of right or left eigenvectors to be
    **          transformed, as returned by chsein or ctrevc.
    **          on exit, v is overwritten by the transformed eigenvectors.
    **
    **  ldv     (input) long int
    **          the leading dimension of the array v. ldv >= max(1,n).
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value.
    **
**/
/////////////////////////////////////////////////////////////////////////////////

namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgebak)(const char* job, const char* side, const nt2_la_int* n,
                               const nt2_la_int* ilo, const nt2_la_int* ihi, const float* scale, const nt2_la_int* m,
                               nt2_la_complex* v, const nt2_la_int* ldv, nt2_la_int* info);
      void NT2_F77NAME(dgebak)(const char* job, const char* side, const nt2_la_int* n,
                               const nt2_la_int* ilo, const nt2_la_int* ihi, const double* scale, const nt2_la_int* m,
                               double* v, const nt2_la_int* ldv, nt2_la_int* info);
      void NT2_F77NAME(sgebak)(const char* job, const char* side, const nt2_la_int* n,
                               const nt2_la_int* ilo, const nt2_la_int* ihi, const float* scale, const nt2_la_int* m,
                               float* v, const nt2_la_int* ldv, nt2_la_int* info);
      void NT2_F77NAME(zgebak)(const char* job, const char* side, const nt2_la_int* n,
                               const nt2_la_int* ilo, const nt2_la_int* ihi, const double* scale, const nt2_la_int* m,
                               nt2_la_complex* v, const nt2_la_int* ldv, nt2_la_int* info);
    }

#define NT2_GEBAK(NAME, T)                      \
  inline void gebak(const char* job,            \
                    const char* side,           \
                    const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    const T* scale,             \
                    const nt2_la_int* m,        \
                    T* v,                       \
                    const nt2_la_int* ldv,      \
                    nt2_la_int* info,           \
                    workspace<T> &)             \
  {                                             \
    NT2_F77NAME( NAME )(job, side, n,           \
                    ilo, ihi, scale,            \
                    m, v, ldv,                  \
                    info);                      \
  }                                             \
  inline void gebak(const char* job,            \
                    const char* side,           \
                    const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    const T* scale,             \
                    const nt2_la_int* m,        \
                    T* v,                       \
                    const nt2_la_int* ldv,      \
                    nt2_la_int* info)           \
  {                                             \
    workspace<T> w;                             \
    gebak(job, side, n,                         \
          ilo, ihi, scale,                      \
          m, v, ldv,                            \
          info, w);                             \
  }                                             \
        /**/

    NT2_GEBAK(sgebak, float)
    NT2_GEBAK(dgebak, double)

#undef NT2_GEBAK

#define NT2_GEBAK(NAME, T, TBASE)               \
  inline void gebak(const char* job,            \
                    const char* side,           \
                    const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    const TBASE* scale,         \
                    const nt2_la_int* m,        \
                    T* v,                       \
                    const nt2_la_int* ldv,      \
                    nt2_la_int* info,           \
                    workspace<T> &)             \
  {                                             \
    NT2_F77NAME( NAME )(job, side, n,           \
                    ilo, ihi, scale,            \
                    m, v, ldv,                  \
                    info);                      \
  }                                             \
  inline void gebak(const char* job,            \
                    const char* side,           \
                    const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    const TBASE* scale,         \
                    const nt2_la_int* m,        \
                    T* v,                       \
                    const nt2_la_int* ldv,      \
                    nt2_la_int* info)           \
  {                                             \
    workspace<T> w;                             \
    gebak(job, side, n,                         \
          ilo, ihi, scale,                      \
          m, v, ldv,                            \
          info, w);                             \
  }                                             \
          /**/

    NT2_GEBAK(cgebak, std::complex<float>, float)
    NT2_GEBAK(zgebak, std::complex<double>, double)

#undef NT2_GEBAK
      } }

#endif

