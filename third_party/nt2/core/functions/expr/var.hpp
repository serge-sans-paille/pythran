//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_VAR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_VAR_HPP_INCLUDED

#include <nt2/core/functions/var.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/var.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/wmean.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/minusone.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type real_type;
    typedef typename meta::call < tag::center_(A0 const &)>::type T2;
    typedef typename meta::call < tag::asum2_(T2)>::type T3;
    typedef typename meta::call < tag::multiplies_(real_type, T3)>::type result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      real_type n = nt2::size(a0, nt2::firstnonsingleton(a0));
      real_type f =  (n <= One<real_type>()) ? One<real_type>() : rec(minusone(n));
      return nt2::multiplies(f, asum2(center(a0)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type real_type;
    typedef typename meta::call < tag::center_(A0 const&, const A1&)>::type T2;
    typedef typename meta::call < tag::asum2_(T2, const A1&)>::type T3;
    typedef typename meta::call < tag::multiplies_(real_type, T3)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      real_type n = nt2::size(a0, nt2::firstnonsingleton(a0));
      real_type n1 = n - (a1 ? 0 : 1);
      real_type f = (n <= One<real_type>())? One<real_type>() :  nt2::rec(n1);
      return nt2::multiplies(f, asum2(center(a0, a1), a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type real_type;
    typedef typename meta::call < tag::center_(A0 const&, A2 const&)>::type T2;
    typedef typename meta::call < tag::asum2_(T2, A2 const &)>::type T3;
    typedef typename meta::call < tag::multiplies_(real_type, T3)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1, const A2& a2) const
    {
      BOOST_ASSERT_MSG(a1 == 0 || a1 == 1, "integer value a1 must be 0 or 1");
      real_type n = nt2::size(a0, a2);
      real_type n1 = n - (a1 ? 0 : 1);
      real_type f = (n <= One<real_type>())? One<real_type>() :  nt2::rec(n1);
      return nt2::multiplies(f, asum2(center(a0, a2), a2));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              )
  {
    typedef typename meta::call < tag::center_(A0 const&, A1 const &)>::type T2;
    typedef typename meta::call < tag::sqr_abs_(T2)>::type T3;
    typedef typename meta::call < tag::wmean_(T3)>::type result_type;
    typedef typename A0::extent_type     ext_t;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w) const
    {
      BOOST_ASSERT_MSG(numel(w) == size(a0, nt2::firstnonsingleton(a0)), "a0 and w have incompatible dimensions");
      //      BOOST_ASSERT_MSG(nt2::all(w > 0), "w must have only strictly positive elements");

      // TO BE PUT IN center or center with w param
      //       value_type m = sum(w(_));
      //       nt2::of_size_max wresize = ones(1,max(ext_t::static_size,dim));
      //       wresize[dim-1] = n;
      //       w = nt2::reshape(w/m, wresize);
      //      value_type f =  nt2::rec(nt2::sum(w(_)));
      return nt2::wmean(nt2::sqr_abs(nt2::center(a0, w)), w);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::call < tag::center_(A0 const&, A1 const &, A2 const&)>::type T2;
    typedef typename meta::call < tag::sqr_abs_(T2)>::type T3;
    typedef typename meta::call < tag::wmean_(T3, const A1&, const A2&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& a2) const
    {
      BOOST_ASSERT_MSG(numel(w) == size(a0, a2), "a0 and w have incompatible dimensions");
      return nt2::wmean(nt2::sqr_abs(nt2::center(a0, w, a2)), w, a2);
    }
  };


} }

#endif
