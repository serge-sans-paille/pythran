//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POTRF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_POSITIVE_DEFINITE_POTRF_HPP_INCLUDED

#include <nt2/linalg/functions/potrf.hpp>
#include <nt2/linalg/details/lapack/declare/potrf.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::potrf_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, double_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        NT2_F77NAME(dpotrf) (&a1,&n,a0.raw(),&lda,&that);

        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::potrf_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, single_<A0>, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        NT2_F77NAME(spotrf) (&a1,&n,a0.raw(),&lda,&that);

        return that;
     }
  };

  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::potrf_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<double_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        NT2_F77NAME(zpotrf) (&a1,&n,a0.raw(),&lda,&that);

        return that;
     }
  };


  /// INTERNAL ONLY - Compute the workspace
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::potrf_, tag::cpu_
                            , (A0)(S0)(A1)
                            , ((container_< nt2::tag::table_, complex_<single_<A0> >, S0 >))
                              (scalar_< ints8_<A1> >)
                            )
  {
     typedef nt2_la_int result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
     {
        result_type that;
        nt2_la_int n   = nt2::width(a0);
        nt2_la_int lda = a0.leading_size();

        NT2_F77NAME(cpotrf) (&a1,&n,a0.raw(),&lda,&that);

        return that;
     }
  };
} }

#endif
