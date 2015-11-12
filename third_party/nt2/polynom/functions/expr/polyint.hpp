//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYINT_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYINT_HPP_INCLUDED
#include <nt2/include/functions/polyint.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyint_, tag::cpu_,
                              (A0),
                              (scalar_<unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                           ( polyint(nt2::_(a0, a0)))
                          )
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyint_, tag::cpu_
                              , (A0)(A1)
                              , ((ast_<A0, nt2::container::domain>))
                              (scalar_<unspecified_<A1> >)
                            )
  {

    typedef typename A0::value_type                                                      value_type;
    typedef typename meta::as_real<value_type>::type                                      real_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(real_type, real_type, real_type)>::type    T0;
    typedef typename nt2::meta::call<nt2::tag::divides_(const A0&, T0)>::type                    T1;
    typedef typename nt2::meta::call<nt2::tag::horzcat_(T1, value_type)>::type          result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::cath(a0/nt2::_(real_type(nt2::numel(a0)), Mone<real_type>(), One<real_type>()), value_type(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyint_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type                                                       value_type;
    typedef typename nt2::meta::call<nt2::tag::polyint_(const A0 &,  value_type)>::type  result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::polyint(a0, Zero<value_type>());
    }
  };

} }


#endif
