//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_PUTALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_PUTALONG_HPP_INCLUDED

#include <nt2/core/functions/putalong.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::putalong_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::extent_type                      base_t;
    typedef typename make_size<base_t::static_size>::type ext_t;

    static BOOST_FORCEINLINE ext_t local_size(A0 const& a0, A1 const& a1)
    {
      ext_t that(1);
      that[a1-1] = nt2::numel(a0);
      return that;
    }

    BOOST_DISPATCH_RETURNS( 2, (A0 const& a0, A1 const& a1)
                          , (nt2::reshape(a0, local_size(a0, a1)))
                          )
  };
} }

#endif
