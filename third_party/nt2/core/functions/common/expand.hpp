//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_EXPAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_EXPAND_HPP_INCLUDED

#include <nt2/core/functions/expand.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/isinside.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::expand_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                         result_type;
    typedef typename meta::as_index<result_type>::type  i_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // We get current position as a subscript
      BOOST_AUTO_TPL( s
                    , as_subscript( boost::proto
                                         ::value(boost::proto::child_c<1>(a0))
                                  , enumerate<i_t>(p)
                                  )
                    );

      // This code select between the actual values and 0 depending on the
      // fact that the current linear index, once turned into a subscript of
      // the destination matrix, is inside the old one.
      return  nt2::if_else
              ( isinside( s, boost::proto::child_c<0>(a0) )
              , nt2::run( boost::proto::child_c<0>(a0)
                        , nt2::min
                          ( splat<i_t>( boost::proto
                                        ::value(boost::proto::child_c<2>(a0))
                                      )
                          , as_index(boost::proto::child_c<0>(a0).extent(), s)
                          )
                        , t
                        )
              , Zero<result_type>()
              );
    }
  };
} }

#endif
