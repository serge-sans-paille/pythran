//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_BLAS_SM_HPP_INCLUDED
#define NT2_LINALG_DETAILS_BLAS_SM_HPP_INCLUDED

#include <complex>
#include <boost/preprocessor/cat.hpp>
#include <nt2/linalg/details/blas/blas3.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
#define NT2_SM(T, PREFIX)                                                       \
inline void trsm( const char *side, const char *uplo, const char *transa        \
                , const char * diag, const long int *m, const long int *n       \
                , const T *al, const T *a, const long int *lda                  \
                , T *b, const long int *ldb                                     \
                )                                                               \
{                                                                               \
  NT2_F77NAME(BOOST_PP_CAT(PREFIX,trsm))(side,uplo,transa,m,n,al,a,lda,b,ldb);  \
}                                                                               \
/**/

  // INTERNAL ONLY
  // all sm call: trsm for data types float, double and related complex
  NT2_SM(double, d)
  NT2_SM(float,  s)
  NT2_SM(std::complex<double>, z)
  NT2_SM(std::complex<float>, c)

#undef NT2_SM
} }

#endif
