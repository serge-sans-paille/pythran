//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GEHRD_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GEHRD_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>

/*! \file gehrd_itf.hh
    (excerpt adapted from xgehrd.f file commentaries)

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
    **  xgehrd reduces a DATA TYPE general matrix a to upper hessenberg form h
    **  by a unitary similarity transformation:  q' * a * q = h .
    **
    **  arguments
    **  =========
    **
    **  n       (input) long int
    **          the order of the matrix a.  n >= 0.
    **
    **  ilo     (input) long int
    **  ihi     (input) long int
    **          it is assumed that a is already upper triangular in rows
    **          and columns 1:ilo-1 and ihi+1:n. ilo and ihi are normally
    **          set by a previous call to cgebal; otherwise they should be
    **          set to 1 and n respectively. see further details.
    **          1 <= ilo <= ihi <= n, if n > 0; ilo=1 and ihi=0, if n=0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the n-by-n general matrix to be reduced.
    **          on exit, the upper triangle and the first subdiagonal of a
    **          are overwritten with the upper hessenberg matrix h, and the
    **          elements below the first subdiagonal, with the array tau,
    **          represent the unitary matrix q as a product of elementary
    **          reflectors. see further details.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,n).
    **
    **  tau     (output) DATA TYPE array, dimension (n-1)
    **          the scalar factors of the elementary reflectors (see further
    **          details). elements 1:ilo-1 and ihi:n-1 of tau are set to
    **          zero.
    **
    **
    **
    **  info    (output) long int
    **          = 0:  successful exit
    **          < 0:  if info = -i, the i-th argument had an illegal value.
    **
    **  further details
    **  ===============
    **
    **  the matrix q is represented as a product of (ihi-ilo) elementary
    **  reflectors
    **
    **     q = h(ilo) h(ilo+1) . . . h(ihi-1).
    **
    **  each h(i) has the form
    **
    **     h(i) = i - tau * v * v'
    **
    **  where tau is a DATA TYPE scalar, and v is a DATA TYPE vector with
    **  v(1:i) = 0, v(i+1) = 1 and v(ihi+1:n) = 0; v(i+2:ihi) is stored on
    **  exit in a(i+2:ihi,i), and tau in tau(i).
    **
    **  the contents of a are illustrated by the following example, with
    **  n = 7, ilo = 2 and ihi = 6:
    **
    **  on entry,                        on exit,
    **
    **  ( a   a   a   a   a   a   a )    (  a   a   h   h   h   h   a )
    **  (     a   a   a   a   a   a )    (      a   h   h   h   h   a )
    **  (     a   a   a   a   a   a )    (      h   h   h   h   h   h )
    **  (     a   a   a   a   a   a )    (      v2  h   h   h   h   h )
    **  (     a   a   a   a   a   a )    (      v2  v3  h   h   h   h )
    **  (     a   a   a   a   a   a )    (      v2  v3  v4  h   h   h )
    **  (                         a )    (                          a )
    **
    **  where a denotes an element of the original matrix a, h denotes a
    **  modified element of the upper hessenberg matrix h, and vi denotes an
    **  element of the vector defining h(i).
    **
**/
/////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  // (excerpt adapted from sgehrd.f)
  //    *  WORK    (workspace/output) float array, dimension (LWORK)
  //    *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //    *
  //    *  LWORK   (input) long int
  //    *          The length of the array WORK.  LWORK >= max(1,N).
  //    *          For optimum performance LWORK >= N*NB, where NB is the
  //    *          optimal blocksize.
  //    *
  //    *          If LWORK = -1, then a workspace query is assumed; the routine
  //    *          only calculates the optimal size of the WORK array, returns
  //    *          this value as the first entry of the WORK array, and no error
  //    *          message related to LWORK is issued by XERBLA.
  //    *
  /////////////////////////////////////////////////////////////////////////

namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(cgehrd)(const nt2_la_int* n, const nt2_la_int* ilo, const nt2_la_int* ihi,
                               nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* tau,
                               nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(dgehrd)(const nt2_la_int* n, const nt2_la_int* ilo, const nt2_la_int* ihi,
                               double* a, const nt2_la_int* lda, double* tau,
                               double* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(sgehrd)(const nt2_la_int* n, const nt2_la_int* ilo, const nt2_la_int* ihi,
                               float* a, const nt2_la_int* lda, float* tau,
                               float* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(zgehrd)(const nt2_la_int* n, const nt2_la_int* ilo, const nt2_la_int* ihi,
                               nt2_la_complex* a, const nt2_la_int* lda, nt2_la_complex* tau,
                               nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
    }

#define NT2_GEHRD(NAME, T)                      \
  inline void gehrd(                            \
                    const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* tau,                     \
                    nt2_la_int* info,           \
            nt2::details::workspace<T> & w)     \
  {                                             \
    NT2_F77NAME( NAME )(n, ilo, ihi,            \
                        a, lda,                 \
                        tau, w.main(),          \
                        query(), info);         \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(n, ilo, ihi,            \
                        a, lda, tau,            \
                        w.getw(), &wn,          \
                        info);                  \
  }                                             \
  inline void gehrd(const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* tau,                     \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gehrd(n, ilo, ihi,                          \
          a, lda, tau,                          \
          info, w);                             \
  }                                             \
        /**/

    NT2_GEHRD(sgehrd, float)
    NT2_GEHRD(dgehrd, double)

#undef NT2_GEHRD


#define NT2_GEHRD(NAME, T, TBASE)               \
  inline void gehrd(const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* tau,                     \
                    nt2_la_int* info,           \
            nt2::details::workspace<T> & w)     \
  {                                             \
    NT2_F77NAME( NAME )(n, ilo, ihi,            \
                        a, lda, tau,            \
                        w.main(), query(),      \
                        info);                  \
    nt2_la_int wn = w.main_need();              \
    w.resize_main(wn);                          \
    NT2_F77NAME( NAME )(n, ilo, ihi,            \
                        a, lda, tau,            \
                        w.main(), &wn, info);   \
  }                                             \
  inline void gehrd(const nt2_la_int* n,        \
                    const nt2_la_int* ilo,      \
                    const nt2_la_int* ihi,      \
                    T* a,                       \
                    const nt2_la_int* lda,      \
                    T* tau,                     \
                    nt2_la_int* info)           \
  {                                             \
    nt2::details::workspace<T> w;               \
    gehrd(n, ilo, ihi, a, lda, tau, info, w);   \
  }                                             \
          /**/

    NT2_GEHRD(cgehrd, std::complex<float>,  float)
    NT2_GEHRD(zgehrd, std::complex<double>, double)
#undef NT2_GEHRD
} }

#endif

