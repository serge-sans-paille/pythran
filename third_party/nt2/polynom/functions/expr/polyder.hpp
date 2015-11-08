//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYDER_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYDER_HPP_INCLUDED
#include <nt2/polynom/functions/polyder.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyder_, tag::cpu_,
                              (A0),
                              (scalar_<floating_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                           ( polyder(nt2::_(a0, a0)))
                          )
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyder_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type                                      real_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(real_type, real_type, real_type)>::type    T0;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                     T1;
    typedef typename nt2::meta::call<nt2::tag::function_(const typename A0::nt2_expression&, size_t, T1)>::type           T2;
    typedef typename nt2::meta::call<nt2::tag::multiplies_(T2, T0)>::type               result_type;
    NT2_FUNCTOR_CALL(1)
    {
      size_t na0 = nt2::numel(a0);
      na0 =  na0 ? na0-1u:0u;
      return nt2::multiplies(a0(One<size_t>(), nt2::_(nt2::One<size_t>(), na0)),
                             nt2::_(real_type(na0), nt2::Mone<real_type>(), One<real_type>()));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyder_, tag::cpu_
                              , (A0)(A1)
                              , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::conv_(const A0&,  const A1&)>::type  T0;
    typedef typename nt2::meta::call<nt2::tag::polyder_(T0)>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::polyder(nt2::conv(a0, a1));
    }
  };
} }


#endif
