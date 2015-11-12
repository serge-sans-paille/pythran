//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ADJFUN_HPP_INCLUDED

#include <nt2/core/functions/adjfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/functions/simd/inc.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::adjfun_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                     result_type;
    typedef typename boost::proto::result_of::child_c<A0&, 0>::value_type   v_t;
    typedef typename boost::simd::ext::adapt_data<v_t,Data>::type      target_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const&) const
    {
      // Types for indices computation
      typedef typename A0::extent_type                                  ext_t;
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename result_of::as_subscript<ext_t,i_t>::type         sub_t;

      // Compute position and shifted position
      sub_t pos0 = as_subscript(a0.extent(), enumerate<i_t>(p));

      sub_t pos1 = pos0;
      ++pos1[boost::proto::value(boost::proto::child_c<1>(a0))];

      // Run the functor on shifted data and original data
      return boost::proto::value(boost::proto::child_c<2>(a0))
            ( nt2::run( boost::proto::child_c<0>(a0)
                      , as_index(boost::proto::child_c<0>(a0).extent(), pos1)
                      , target_t()
                      )
            , nt2::run( boost::proto::child_c<0>(a0)
                      , as_index(boost::proto::child_c<0>(a0).extent(), pos0)
                      , target_t()
                      )
            );
    }
  };
} }

#endif
