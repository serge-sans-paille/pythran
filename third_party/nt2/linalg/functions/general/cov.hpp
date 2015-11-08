//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_COV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_COV_HPP_INCLUDED

#include <nt2/include/functions/cov.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ifvectvert.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/zeros.hpp>

//strange dispatching is to mimick matlab cov function

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))(scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call<tag::ifvectvert_(A0 const&)>::type T0;
    typedef typename meta::call<tag::center_(T0, size_t)>::type T1;
    typedef typename meta::call<tag::conj_(T1)>::type T2;
    typedef typename meta::call<tag::transpose_(T2)>::type T3;
    typedef typename meta::call<tag::mtimes_(T3, T1)>::type T4;
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::multiplies_(T4,value_type)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const & a1) const
    {
       T0 a00 = nt2::ifvectvert(a0);
       T1 a0_c = nt2::center(a00, size_t(1));
       size_t n = nt2::size(a00, 1);
       value_type f = (n <= 1u)? One<value_type>() : nt2::rec(value_type(n)-(a1?value_type(0):value_type(1)));
       return  nt2::multiplies(nt2::mtimes(trans(conj(a0_c)), a0_c), f);
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename meta::call<tag::ifvectvert_(A0 const&)>::type T0;
    typedef typename meta::call<tag::center_(T0, size_t)>::type T1;
    typedef typename meta::call<tag::conj_(T1)>::type T2;
    typedef typename meta::call<tag::transpose_(T2)>::type T3;
    typedef typename meta::call<tag::mtimes_(T3, T1)>::type T4;
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::multiplies_(T4, value_type)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      T0 a00 = nt2::ifvectvert(a0);
      T1 a0_c = nt2::center(a00, size_t(1));
      size_t n = nt2::size(a00, 1);
      value_type f = (n <= 1u)? One<value_type>() : nt2::rec(minusone(value_type(n)));
      return  nt2::multiplies(nt2::mtimes(trans(conj(a0_c)), a0_c), f);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))
                              )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           nt2::cov(nt2::horzcat(a0(nt2::_), a1(nt2::_)))
                           )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))(scalar_<integer_<A2> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
                           nt2::cov(nt2::horzcat(a0(nt2::_), a1(nt2::_)), a2)
                           )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0),
                              (scalar_<unspecified_<A0> >)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return Zero<A0>();
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const &) const
    {
      return Zero<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 2, (A0 const& a0, A1 const& a1)
                                , (A0 const&, A1 const&)
                                , nt2::zeros(2, 2, nt2::meta::as_<A0>())
                                )
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 3, (A0 const& a0, A1 const& a1, A2 const& a2)
                                , (A0 const&, A1 const&, A2)
                                , nt2::zeros(2, 2, nt2::meta::as_<A0>())
                                )
  };
} }

#endif
