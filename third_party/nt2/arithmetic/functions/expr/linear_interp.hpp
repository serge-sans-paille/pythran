//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_EXPR_LINEAR_INTERP_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_EXPR_LINEAR_INTERP_HPP_INCLUDED

#include <nt2/arithmetic/functions/linear_interp.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/fma.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename meta::call<tag::oneminus_(const A0&)>::type                       T0;
    typedef typename meta::call<tag::sx_(tag::multiplies_, T0,const A1&)>::type               T1;
    typedef typename meta::call<tag::sx_(tag::fma_, const A0&,const A2&, T1)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& dx, A1 const& a, A2 const& b) const
    {
      return nt2::sx(nt2::tag::fma_(), dx, b, nt2::sx(nt2::tag::multiplies_(), nt2::oneminus(dx), a));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (generic_<floating_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename meta::call<tag::oneminus_(const A0&)>::type                        T0;
    typedef typename meta::call<tag::multiplies_(T0,const A1&)>::type                   T1;
    typedef typename meta::call<tag::multiplies_(const A0&,const A2&)>::type            T2;
    typedef typename meta::call<tag::sx_(tag::plus_,T2,T1)>::type                    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& dx, A1 const& a, A2 const& b) const
    {
      return nt2::sx(nt2::tag::plus_(), dx*b, nt2::oneminus(dx)*a);
    }
  };

} }

#endif
