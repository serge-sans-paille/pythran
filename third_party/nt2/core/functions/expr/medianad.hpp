//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MEDIANAD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MEDIANAD_HPP_INCLUDED

#include <nt2/core/functions/medianad.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/median.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::medianad_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
    )
  {
    typedef typename meta::call<tag::medianad_(A0 const&, std::size_t)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      std::size_t dim = nt2::firstnonsingleton(a0);
      return nt2::medianad(a0,dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::medianad_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef typename meta::call<tag::median_(A0 const&, A1 const&)>::type          T0;
    typedef typename meta::call<tag::extent_(A0 const&)>::type                     E0;
    typedef typename meta::call<tag::expand_to_(T0, E0)>::type                    T0b;
    typedef typename meta::call<tag::minus_(A0 const &, T0b)>::type                T1;
    typedef typename meta::call<tag::abs_(T1)>::type                               T2;
    typedef typename meta::call<tag::median_(T2, A1 const&)>::type        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& dim) const
    {
      BOOST_AUTO_TPL(t0, nt2::median(a0, dim));
      BOOST_AUTO_TPL(t1, a0 - nt2::expand_to(t0, extent(a0)));
      BOOST_AUTO_TPL(t2, nt2::abs(t1));
      BOOST_AUTO_TPL(t3,nt2::median(t2, dim));
      return t3;
    }
  };
} }

#endif
