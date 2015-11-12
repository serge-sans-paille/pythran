//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_GQR_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_GQR_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
// its a mix or orgqr and ungqr
// dorgqr generates an m-by-n real matrix q with orthonormal columns,
// *  which is defined as the first n columns of a product of k elementary
// *  reflectors of order m
// *
// *        q  =  h(1) h(2) . . . h(k)
// *
// *  as returned by dgeqrf.
// *
// *  arguments
// *  =========
// *
// *  m       (input) integer
// *          the number of rows of the matrix q. m >= 0.
// *
// *  n       (input) integer
// *          the number of columns of the matrix q. m >= n >= 0.
// *
// *  k       (input) integer
// *          the number of elementary reflectors whose product defines the
// *          matrix q. n >= k >= 0.
// *
// *  a       (input/output) double precision array, dimension (lda,n)
// *          on entry, the i-th column must contain the vector which
// *          defines the elementary reflector h(i), for i = 1,2,...,k, as
// *          returned by dgeqrf in the first k columns of its array
// *          argument a.
// *          on exit, the m-by-n matrix q.
// *
// *  lda     (input) integer
// *          the first dimension of the array a. lda >= max(1,m).
// *
// *  tau     (input) double precision array, dimension (k)
// *          tau(i) must contain the scalar factor of the elementary
// *          reflector h(i), as returned by dgeqrf.
// *
// *  work    (workspace/output) double precision array, dimension (max(1,lwork))
// *          on exit, if info = 0, work(1) returns the optimal lwork.
// *
// *  lwork   (input) integer
// *          the dimension of the array work. lwork >= max(1,n).
// *          for optimum performance lwork >= n*nb, where nb is the
// *          optimal blocksize.
// *
// *          if lwork = -1, then a workspace query is assumed; the routine
// *          only calculates the optimal size of the work array, returns
// *          this value as the first entry of the work array, and no error
// *          message related to lwork is issued by xerbla.
// *
// *  info    (output) integer
// *          = 0:  successful exit
// *          < 0:  if info = -i, the i-th argument has an illegal value

namespace nt2
{
  namespace details
  {
    extern "C"
    {
      void NT2_F77NAME(dorgqr)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           double* a, const nt2_la_int* lda, const double* tau,
                           double* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(sorgqr)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           float* a, const nt2_la_int* lda, const float* tau,
                           float* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(zungqr)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           nt2_la_complex* a, const nt2_la_int* lda, const nt2_la_complex* tau,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
      void NT2_F77NAME(cungqr)(const nt2_la_int* m, const nt2_la_int* n, const nt2_la_int* k,
                           nt2_la_complex* a, const nt2_la_int* lda, const nt2_la_complex* tau,
                           nt2_la_complex* work, const nt2_la_int* lwork, nt2_la_int* info);
    }

#define NT2_GQR(NAME, T)                                  \
    inline void gqr(const nt2_la_int* m,                  \
                    const nt2_la_int* n,                  \
                    const nt2_la_int* k,                  \
                    T* a,                                 \
                    const nt2_la_int* lda,                \
                    const T* tau,                         \
                    nt2_la_int* info,                     \
                    nt2::details::workspace<T> & w)       \
    {                                                     \
      NT2_F77NAME(NAME)(m,n,k,a,lda,                      \
                        tau,w.main(),query(),             \
                        info);                            \
      nt2_la_int wn = w.main_need();                      \
      w.resize_main(wn);                                  \
      NT2_F77NAME(NAME)(m,n,k,a,lda,tau,                  \
                        w.main(),&wn,                     \
                        info);                            \
    }                                                     \
    inline void gqr(const nt2_la_int* m,                  \
                    const nt2_la_int* n,                  \
                    const nt2_la_int* k,                  \
                    T* a,                                 \
                    const nt2_la_int* lda,                \
                    const T* tau,                         \
                    nt2_la_int* info)                     \
    {                                                     \
      nt2::details::workspace<T> w;                       \
      gqr(m, n, k, a, lda, tau, info, w);                 \
    }                                                     \

    NT2_GQR(sorgqr, float)
    NT2_GQR(dorgqr, double)

#undef NT2_GQR

#define NT2_GQR(NAME, T, TBASE)                           \
      inline void gqr( const nt2_la_int* m,               \
                       const nt2_la_int* n,               \
                       const nt2_la_int* k,               \
                       T* a,                              \
                       const nt2_la_int* lda,             \
                       const T* tau,                      \
                       nt2_la_int* info,                  \
                       nt2::details::workspace<T> & w)    \
      {                                                   \
        NT2_F77NAME(NAME)(m,n,k,a,lda,tau,                \
                          w.main(),query(),               \
                          info);                          \
        nt2_la_int wn = w.main_need();                    \
        w.resize_main(wn);                                \
        NT2_F77NAME(NAME)(m,n,k,a,lda,tau,                \
                          w.main(),&wn,                   \
                          info);                          \
      }                                                   \
      inline void gqr(const nt2_la_int* m,                \
                        const nt2_la_int* n,              \
                        const nt2_la_int* k,              \
                        T* a,                             \
                        const nt2_la_int* lda,            \
                        const T* tau,                     \
                        nt2_la_int* info)                 \
      {                                                   \
        nt2::details::workspace<T> w;                     \
        gqr(m, n, k, a, lda, tau, info, w);               \
      }                                                   \

    NT2_GQR(cungqr, std::complex<float>,  float)
    NT2_GQR(zungqr, std::complex<double>, double)

#undef NT2_GQR


  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of gqr.hpp
// /////////////////////////////////////////////////////////////////////////////
