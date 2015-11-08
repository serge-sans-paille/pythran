//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_BLAS1_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_BLAS1_HPP_INCLUDED

#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  // Real, double precision
  double NT2_F77NAME(dasum)(const nt2_la_int* n, const double *dx, const nt2_la_int* incx);

  void NT2_F77NAME(daxpy)(const nt2_la_int* n, const double *da, const double *dx,
                          const nt2_la_int* incx, double *dy, const nt2_la_int* incy);

  void NT2_F77NAME(dcopy)(const nt2_la_int* n, double *dx, const nt2_la_int* incx,
                      double *dy, const nt2_la_int* incy);

  double NT2_F77NAME(ddot)(const nt2_la_int* n, const double *dx, const nt2_la_int* incx,
                       const double *dy, const nt2_la_int* incy);

  double NT2_F77NAME(dnrm2)(const nt2_la_int* n, const double *dx, const nt2_la_int* incx);

  void NT2_F77NAME(drot)(const nt2_la_int* n, double *dx, const nt2_la_int* incx,
                     double *dy, const nt2_la_int* incy, const double *c,
                     const double *s);

  void NT2_F77NAME(drotg)(double *da, double *db, double *c, double *s);

  void NT2_F77NAME(dscal)(const nt2_la_int* n, double *da, double *dx,
                      const nt2_la_int* incx);

  void NT2_F77NAME(dswap)(const nt2_la_int* n, double *dx, const nt2_la_int* incx,
                      double *dy, const nt2_la_int* incy);

  long int NT2_F77NAME(idamax)(const nt2_la_int* n, const double *dx,
                           const nt2_la_int* incx);

  // Real, single precision

  float NT2_F77NAME(sasum)(const nt2_la_int* n, const float *dx, const nt2_la_int* incx);


  void NT2_F77NAME(saxpy)(const nt2_la_int* n, const float *da, const float *dx,
                      const nt2_la_int* incx, float *dy, const nt2_la_int* incy);

  void NT2_F77NAME(scopy)(const nt2_la_int* n, float *dx, const nt2_la_int* incx, float *dy,
                      const nt2_la_int* incy);

  float NT2_F77NAME(sdot)(const nt2_la_int* n, const float *dx, const nt2_la_int* incx,
                      const float *dy, const nt2_la_int* incy);

  float NT2_F77NAME(snrm2)(const nt2_la_int* n, const float *dx, const nt2_la_int* incx);

  void NT2_F77NAME(srot)(const nt2_la_int* n, float *dx, const nt2_la_int* incx, float *dy,
                     const nt2_la_int* incy, const float *c, const float *s);

  void NT2_F77NAME(srotg)(float *da, float *db, float *c, float *s);

  void NT2_F77NAME(sscal)(const nt2_la_int* n, float *da, float *dx, const nt2_la_int* incx);

  void NT2_F77NAME(sswap)(const nt2_la_int* n, float *dx, const nt2_la_int* incx, float *dy,
                      const nt2_la_int* incy);

  long int NT2_F77NAME(isamax)(const nt2_la_int* n, const float *dx, const nt2_la_int* incx);

  //complex < float >
  float NT2_F77NAME(cdotc)(nt2_la_complex *c, const nt2_la_int* n,
                       const nt2_la_complex *cx, const nt2_la_int* incx,
                       const nt2_la_complex *cy, const nt2_la_int* incy);

  float NT2_F77NAME(cdotu)(nt2_la_complex *c, const nt2_la_int* n,
                       const nt2_la_complex *cx, const nt2_la_int* incx,
                       const nt2_la_complex *cy, const nt2_la_int* incy);

  void NT2_F77NAME(caxpy)(const nt2_la_int* n, const nt2_la_complex *da,
                      const nt2_la_complex *dx,
                      const nt2_la_int* incx, nt2_la_complex *dy,
                      const nt2_la_int* incy);

  void NT2_F77NAME(ccopy)(const nt2_la_int* n, nt2_la_complex *dx, const nt2_la_int* incx,
                      nt2_la_complex *dy, const nt2_la_int* incy);

  float  NT2_F77NAME(scasum)(const nt2_la_int* n, const nt2_la_complex *dx,
                         const nt2_la_int* incx);

  float  NT2_F77NAME(scnrm2)(const nt2_la_int* n, const nt2_la_complex *dx,
                         const nt2_la_int* incx);

  void NT2_F77NAME(cdscal)(const nt2_la_int* n, const float *da, nt2_la_complex *dx,
                       const nt2_la_int* incx);

  void NT2_F77NAME(cscal)(const nt2_la_int* n, const nt2_la_complex *da,
                      nt2_la_complex *dx, const nt2_la_int* incx);

  long int NT2_F77NAME(icamax)(const nt2_la_int* n, const nt2_la_complex *dx,
                           const nt2_la_int* incx);

  void NT2_F77NAME(cswap)(const nt2_la_int* n, nt2_la_complex *dx, const nt2_la_int* incx,
                      nt2_la_complex *dy, nt2_la_int* incy);

  //complex < double >
  double NT2_F77NAME(zdotc)(nt2_la_complex *c, const nt2_la_int* n,
                        const nt2_la_complex *cx,
                        const nt2_la_int* incx, const nt2_la_complex *cy,
                        const nt2_la_int* incy);

  double NT2_F77NAME(zdotu)(const nt2_la_complex *c, const nt2_la_int* n,
                        const nt2_la_complex *cx, const nt2_la_int* incx,
                        const nt2_la_complex *cy, const nt2_la_int* incy);

  void NT2_F77NAME(zaxpy)(const nt2_la_int* n, const nt2_la_complex *da,
                      const nt2_la_complex *dx,
                      const nt2_la_int* incx, nt2_la_complex *dy,
                      const nt2_la_int* incy);

  void NT2_F77NAME(zcopy)(const nt2_la_int* n, const nt2_la_complex *dx, const nt2_la_int* incx,
                      nt2_la_complex *dy, const nt2_la_int* incy);

  double  NT2_F77NAME(dzasum)(const nt2_la_int* n, const nt2_la_complex *dx,
                          const nt2_la_int* incx);

  double  NT2_F77NAME(dznrm2)(const nt2_la_int* n, const nt2_la_complex *dx,
                          const nt2_la_int* incx);

  void NT2_F77NAME(zdscal)(const nt2_la_int* n, const double *da, nt2_la_complex *dx,
                       const nt2_la_int* incx);

  void NT2_F77NAME(zscal)(const nt2_la_int* n, const nt2_la_complex *da,
                      nt2_la_complex *dx, const nt2_la_int* incx);

  long int NT2_F77NAME(izamax)(const nt2_la_int* n, const nt2_la_complex *dx,
                           const nt2_la_int* incx);

  void NT2_F77NAME(zswap)(const nt2_la_int* n, nt2_la_complex *dx, const nt2_la_int* incx,
                      nt2_la_complex *dy, nt2_la_int* incy);
}

#endif
