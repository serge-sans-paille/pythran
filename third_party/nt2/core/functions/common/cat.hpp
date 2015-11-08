//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CAT_HPP_INCLUDED

#include <nt2/core/functions/cat.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Target)(N)
                            , ((node_<A0, nt2::tag::cat_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((target_< unspecified_<Target> >))
                            )
  {
    typedef typename Target::type                                   result_type;
    typedef typename A0::extent_type                                ext_t;
    typedef typename meta::as_index<result_type>::type              i_t;
    typedef typename result_of::as_subscript<ext_t,i_t>::type       sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Target const& t) const
    {
      // Gather dimension to concatenate
      std::size_t along = boost::proto::child_c<0>(a0);

      // Gather size of a0 and a1
      ext_t ex0 = boost::proto::child_c<1>(a0).extent();
      ext_t ex1 = boost::proto::child_c<2>(a0).extent();

      // Gather indexing treshold
      i_t offset = splat<i_t>(ex0[along]);

      sub_t pos  = as_subscript(a0.extent(),enumerate<i_t>(p));
      sub_t pos0 = pos;
      sub_t pos1 = pos;

      // Fix position while not going outside an empty table
      pos0[along] = min ( pos[along]
                        , splat<i_t>(ex0[along] ? ex0[along]-1 : ex0[along])
                        );

      pos1[along] = min ( selsub( ge(pos[along],offset), pos[along], offset)
                        , splat<i_t>(ex1[along] ? ex1[along]-1 : ex1[along])
                        );

      // Select the proper value
      return if_else( lt(pos[along], offset)
                    , nt2::run( boost::proto::child_c<1>(a0)
                              , numel(ex0) ? as_index(ex0, pos0) : Zero<i_t>()
                              , t
                              )
                    , nt2::run( boost::proto::child_c<2>(a0)
                              , numel(ex1) ? as_index(ex1, pos1) : Zero<i_t>()
                              , t
                              )
                    );
    }
  };
} }

#endif
