//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYADD_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYADD_HPP_INCLUDED

#include <nt2/polynom/functions/polyadd.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2{ namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyadd_, tag::cpu_,
                              (A0),
                              (scalar_<floating_<A0> >)
                              (scalar_<floating_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           ( polyadd(nt2::_(a0, a0), nt2::_(a1, a1)))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyadd_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<floating_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           ( polyadd(nt2::_(a0, a0), a1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyadd_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<floating_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           ( polyadd(a0, nt2::_(a1, a1)))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyadd_, tag::cpu_
                              , (A0)(A1)
                              , ((ast_<A0, nt2::container::domain>))
                                ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                                                          value_type;
    typedef typename nt2::meta::call<nt2::tag::reduce_(const A0&)>::type                            TA0;
    typedef typename nt2::meta::call<nt2::tag::reduce_(const A1&)>::type                            TA1;
    typedef typename nt2::meta::call<nt2::tag::Zero(size_t, size_t, meta::as_<value_type>)>::type     S;
    typedef typename nt2::meta::call<nt2::tag::horzcat_(S, TA0)>::type                               T0;
    typedef typename nt2::meta::call<nt2::tag::horzcat_(S, TA1)>::type                               T1;
    typedef typename nt2::meta::call<nt2::tag::plus_(T0, T1)>::type                                  T2;
    typedef typename nt2::meta::call<nt2::tag::reduce_(T2)>::type                           result_type;
    result_type operator()(const A0& a, const A1& b) const
    {
      BOOST_AUTO_TPL( aa, nt2::reduce(a));
      BOOST_AUTO_TPL( bb, nt2::reduce(b));
      size_t na =  nt2::numel(aa);
      size_t nb =  nt2::numel(bb);
      size_t n2 =  na > nb ? na-nb : 0;
      size_t n1 =  nb > na ? nb-na : 0;
      BOOST_AUTO_TPL( aaa, nt2::cath(nt2::zeros(nt2::One<size_t>(), n1, meta::as_<value_type>()), aa));
      BOOST_AUTO_TPL( bbb, nt2::cath(nt2::zeros(nt2::One<size_t>(), n2, meta::as_<value_type>()), bb));
      return nt2::reduce(nt2::plus(aaa, bbb));
    }
  };
} }

#endif
