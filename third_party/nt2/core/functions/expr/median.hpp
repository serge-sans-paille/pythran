//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MEDIAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MEDIAN_HPP_INCLUDED

#include <nt2/core/functions/median.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/meanof.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/is_odd.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::median_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type value_type;
    typedef          table<value_type>   tab_t;
    typedef tab_t                  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::median(a0,firstnonsingleton(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::median_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef typename A0::value_type value_type;
    typedef          table<value_type>   tab_t;
    typedef tab_t                  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& dim) const
    {
      tab_t sa0 = nt2::sort(a0, dim, 'a');
      size_t idx = nt2::size(a0, dim);
      size_t mid = idx >> 1;
      if (is_odd(idx))
        return nt2::along(sa0, mid+1 , dim);
      else
        return nt2::meanof(nt2::along(sa0, mid, dim),
                           nt2::along(sa0, mid+1, dim));
    }
  };
} }

#endif
