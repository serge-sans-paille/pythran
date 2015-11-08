//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NANMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NANMEAN_HPP_INCLUDED

#include <nt2/core/functions/nanmean.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/nansum.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/is_not_nan.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nanmean_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename meta::call < nt2::tag::nanmean_(A0 const &, std::size_t)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      std::size_t dim = nt2::firstnonsingleton(a0);
      return nt2::nanmean(a0, dim);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nanmean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type                                            value_type;
    typedef typename meta::call < nt2::tag::nansum_(A0 const &, A1 const &)>::type     T1;
    typedef typename meta::call < nt2::tag::is_not_nan_(A0 const &)>::type             T2;
    typedef typename meta::call < nt2::tag::nbtrue_(T2, A1 const &)>::type             T3;
    typedef typename meta::call < nt2::tag::max_(T3, value_type)>::type               T3b;
    typedef typename meta::call < nt2::tag::rec_(T3b)>::type                           T4;
    typedef typename meta::call < nt2::tag::multiplies_(T4, T1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::multiplies(nt2::rec(nt2::max(nt2::nbtrue(nt2::is_not_nan(a0), a1),
                                               One<value_type>())), nt2::nansum(a0, a1));
    }
  };
} }

#endif
