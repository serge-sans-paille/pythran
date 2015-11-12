//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POSV_HPP_INCLUDED

#include <nt2/linalg/functions/posv.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>


extern "C"
{
  void NT2_F77NAME(dposv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , double* a
                          , const nt2_la_int* lda    , double* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(sposv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , float* a
                          , const nt2_la_int* lda    , float* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(cposv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , nt2_la_complex* a
                          , const nt2_la_int* lda    , nt2_la_complex* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(zposv)(  const char* uplo         , const nt2_la_int* n
                          , const nt2_la_int* nhrs   , nt2_la_complex* a
                          , const nt2_la_int* lda    , nt2_la_complex* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))   // A
                              ((container_< nt2::tag::table_, double_<A1>, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        char uplo = 'L';

        NT2_F77NAME(dposv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                           , &that
                            );

        return that;
     }
  };



  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))   // A
                              ((container_< nt2::tag::table_, single_<A1>, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        char uplo = 'L';


        NT2_F77NAME(sposv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                           , &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))   // A
                              ((container_< nt2::tag::table_, complex_<double_<A1> >, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        char uplo = 'L';

        NT2_F77NAME(zposv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                           , &that
                            );

        return that;
     }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))   // A
                              ((container_< nt2::tag::table_, complex_<single_<A1> >, S1 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type that;
        nt2_la_int  n  = nt2::width(a0);
        nt2_la_int  ld = a0.leading_size();
        nt2_la_int  ldb = a1.leading_size();
        nt2_la_int  nhrs = nt2::width(a1);
        char uplo = 'L';

        NT2_F77NAME(cposv) ( &uplo, &n, &nhrs, a0.raw(), &ld, a1.raw(), &ldb
                           , &that
                            );

        return that;
     }
  };

} }

#endif
