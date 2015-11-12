//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEBAK_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEBAK_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

/*! \file gebak_itf.hh
    (excerpt adapted from xgebak.f file commentaries)

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

#endif
