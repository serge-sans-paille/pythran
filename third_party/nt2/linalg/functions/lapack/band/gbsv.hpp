//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_BAND_GBSV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_BAND_GBSV_HPP_INCLUDED

#include <nt2/linalg/functions/gbsv.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{
  void NT2_F77NAME(dgbsv)(  const nt2_la_int* n      , const nt2_la_int* kl
                          , const nt2_la_int* ku     , const nt2_la_int* nhrs
                          , double* a                , const nt2_la_int* lda
                          , nt2_la_int* ipiv         , double* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(sgbsv)(  const nt2_la_int* n      , const nt2_la_int* kl
                          , const nt2_la_int* ku     , const nt2_la_int* nhrs
                          , float* a                 , const nt2_la_int* lda
                          , nt2_la_int* ipiv         , float* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(cgbsv)(  const nt2_la_int* n      , const nt2_la_int* kl
                          , const nt2_la_int* ku     , const nt2_la_int* nhrs
                          , nt2_la_complex* a        , const nt2_la_int* lda
                          , nt2_la_int* ipiv         , nt2_la_complex* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );

  void NT2_F77NAME(zgbsv)(  const nt2_la_int* n      , const nt2_la_int* kl
                          , const nt2_la_int* ku     , const nt2_la_int* nhrs
                          , nt2_la_complex* a        , const nt2_la_int* lda
                          , nt2_la_int* ipiv         , nt2_la_complex* b
                          , const nt2_la_int* ldb    , nt2_la_int* info
                          );
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >)) // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, double_<A2>, S2 >)) // X

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
      typedef typename meta::option<A0,nt2::tag::shape_>::type shape;

      result_type that;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int nhrs = nt2::width(a2);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;

      a1.resize(nt2::of_size(n,1));

      NT2_F77NAME(dgbsv)(&n,&kl,&ku,&nhrs,a0.raw(),&ld,a1.raw(),a2.raw(),&ld,&that);

      return that;
     }
  };



  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >)) // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, single_<A2>, S2 >)) // X

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
      typedef typename meta::option<A0,nt2::tag::shape_>::type shape;

      result_type that;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int nhrs = nt2::width(a2);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;

      a1.resize(nt2::of_size(n,1));

      NT2_F77NAME(sgbsv)(&n,&kl,&ku,&nhrs,a0.raw(),&ld,a1.raw(),a2.raw(),&ld,&that);

      return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >)) // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >)) // X

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
      typedef typename meta::option<A0,nt2::tag::shape_>::type shape;

      result_type that;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int nhrs = nt2::width(a2);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;

      a1.resize(nt2::of_size(n,1));

      NT2_F77NAME(cgbsv)(&n,&kl,&ku,&nhrs,a0.raw(),&ld,a1.raw(),a2.raw(),&ld,&that);

      return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gbsv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >)) // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // PIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >)) // X

                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
      typedef typename meta::option<A0,nt2::tag::shape_>::type shape;

      result_type that;
      nt2_la_int n = nt2::width(a0);
      nt2_la_int nhrs = nt2::width(a2);
      nt2_la_int ku = shape::ud;
      nt2_la_int kl = shape::ld;
      nt2_la_int ld = n;

      a1.resize(nt2::of_size(n,1));

      NT2_F77NAME(zgbsv)(&n,&kl,&ku,&nhrs,a0.raw(),&ld,a1.raw(),a2.raw(),&ld,&that);

      return that;
     }
  };
} }

#endif
