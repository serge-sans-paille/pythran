//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_EXPAND_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_EXPAND_TO_HPP_INCLUDED

#include <nt2/core/functions/expand_to.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::expand_to_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::proto::result_of::
                     child_c<A0&,0>::value_type                        child0_t;
    typedef typename A0::extent_type                                      ext_t;
    typedef typename Data::type                                     result_type;

    typedef typename meta::as_index<result_type>::type                      i_t;
    typedef typename result_of::as_subscript<ext_t,i_t>::type               s_t;


    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Grab position and size
      s_t pos0  = as_subscript(a0.extent(), enumerate<i_t>(p));
      ext_t sz0 = boost::proto::child_c<0>(a0).extent();

      // If you're a singleton, you're always the smallest
      for(std::size_t i = 0; i != ext_t::size(); ++i)
      {
        pos0[i] = nt2::min(splat<i_t>(sz0[i]-1u), pos0[i]);
      }

      // return each value potentially repeated
      return run(boost::proto::child_c<0>(a0), as_index(sz0, pos0), t);
    }
  };
} }

#endif
