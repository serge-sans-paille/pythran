//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TRAPZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TRAPZ_HPP_INCLUDED

#include <nt2/core/functions/trapz.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/trapz.hpp>
#include <nt2/include/functions/adjfun.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/putalong.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trapz_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename meta::call < tag::trapz_(A0 const&, size_t)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::trapz(a0, nt2::firstnonsingleton(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trapz_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type real_type;
    typedef typename meta::call < tag::adjfun_(nt2::functor<tag::plus_>, A0 const&, const A1&)>::type T2;
    typedef typename meta::call < tag::sum_(T2,const A1&)>::type T3;
    typedef typename meta::call < tag::multiplies_(real_type, T3)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      BOOST_AUTO_TPL(tmp, nt2::adjfun(nt2::functor<nt2::tag::plus_>(), a0, a1 ));
      return nt2::multiplies(Half<real_type>(), nt2::sum(tmp, a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trapz_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                               (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type real_type;
    typedef typename meta::call < tag::adjfun_(functor<nt2::tag::plus_>, const A0&, const A2&)>::type T1;
    typedef typename meta::call < tag::putalong_(const A0&, const A2&)>::type                         T2;
    typedef typename meta::call < tag::diff_(T2, size_t, const A2&)>::type                            T3;
    typedef typename meta::call < tag::extent_(T1)>::type                                            T1b;
    typedef typename meta::call < tag::expand_to_(T3, T1b)>::type                                     T4;
    typedef typename meta::call < tag::dot_(T4, T1, A2 const &)>::type                                T5;
    typedef typename meta::call < tag::multiplies_(real_type, T5)>::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1, const A2& a2) const
    {
      BOOST_AUTO_TPL(tmp1, nt2::adjfun(functor<nt2::tag::plus_>(), a1, a2 ));
      BOOST_AUTO_TPL(tmp2, nt2::putalong(a0, a2));
      BOOST_AUTO_TPL(tmp3, nt2::diff(tmp2, size_t(1), a2));
      BOOST_AUTO_TPL(tmp4, nt2::expand_to(tmp3, extent(tmp1)));
      BOOST_AUTO_TPL(tmp5, nt2::dot(tmp4,tmp1,a2));
      return nt2::multiplies(Half<real_type>(), tmp5);

    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trapz_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
    )
  {
    typedef typename meta::call < tag::trapz_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::trapz(a0, a1, nt2::firstnonsingleton(a0));
    }
  };
} }

#endif
