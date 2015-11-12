//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_GESV_HPP_INCLUDED

#include <nt2/linalg/functions/gesv.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

extern "C"
{
  void NT2_F77NAME(dgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , double* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , double* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(sgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , float* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , float* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(cgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info
                         );

  void NT2_F77NAME(zgesv)( const nt2_la_int* n, const nt2_la_int* nrhs
                         , nt2_la_complex* a, const nt2_la_int* lda, nt2_la_int* ipiv
                         , nt2_la_complex* b, const nt2_la_int* ldb, nt2_la_int* info
                         );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, double_<A2>, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        NT2_F77NAME(dgesv)(&n,&nhrs,a0.raw(),&lda,a1.raw(),a2.raw(),&ldb,&that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, single_<A2>, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        NT2_F77NAME(sgesv)(&n,&nhrs,a0.raw(),&lda,a1.raw(),a2.raw(),&ldb,&that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, complex_<double_<A2> >, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        NT2_F77NAME(zgesv)(&n,&nhrs,a0.raw(),&lda,a1.raw(),a2.raw(),&ldb,&that);

        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gesv_, tag::cpu_
                            , (A0)(S0)(A1)(S1)(A2)(S2)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))  // A
                              ((container_< nt2::tag::table_, integer_<A1>, S1 >)) // IPIV
                              ((container_< nt2::tag::table_, complex_<single_<A2> >, S2 >))   // B
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2& a2) const
     {
        result_type that;
        nt2_la_int  n  = std::min(nt2::height(a0),nt2::width(a0));
        nt2_la_int  lda = n;
        nt2_la_int  nhrs = nt2::width(a2);
        nt2_la_int  ldb = a2.leading_size();

        a1.resize(nt2::of_size(n,1));

        NT2_F77NAME(cgesv)(&n,&nhrs,a0.raw(),&lda,a1.raw(),a2.raw(),&ldb,&that);

        return that;
     }
  };
} }

#endif
