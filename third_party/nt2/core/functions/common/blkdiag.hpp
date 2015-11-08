//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::blkdiag_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                                 result_type;
    typedef typename meta::as_index<result_type>::type                  i_t;
    typedef typename result_of::as_subscript<_2D, i_t>::type          sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Get size of each children
      _2D ex0 = boost::proto::child_c<0>(a0).extent();
      _2D ex1 = boost::proto::child_c<1>(a0).extent();

      std::size_t n0 = numel(ex0);
      std::size_t n1 = numel(ex1);

      // Get the current index vector
      sub_t pos = as_subscript(_2D(a0.extent()),nt2::enumerate<i_t>(p));

      i_t const offset0 = splat<i_t>(ex0[0]);
      i_t const offset1 = splat<i_t>(ex0[1]);

      // Find the proper quadrant for each position
      typedef typename meta::as_logical<i_t>::type mask_t;
      i_t  vn0 = splat<i_t>(n0);
      mask_t const is_stack0 = l_and(nt2::lt(pos[1],offset1), nt2::is_nez(vn0));
      mask_t const is_row0   = nt2::lt(pos[0],offset0);

      // Boundaries for indexes
      i_t bound0 = splat<i_t>(n0 ? n0-1 : n0);
      i_t bound1 = splat<i_t>(n1 ? n1-1 : n1);

      // Result is out of the diagonal
      result_type const z   = Zero<result_type>();
      i_t         const zi  = Zero<i_t>();

      // Result is from a0
      result_type const s0 = nt2::run ( boost::proto::child_c<0>(a0)
                                      , n0  ? min (  as_index(ex0, pos)
                                                  , bound0
                                                  )
                                            : zi
                                      , t
                                      );

      // Compute offset to find other possible data
      pos[0] = selsub( ge(pos[0],offset0), pos[0], offset0);
      pos[1] = selsub( ge(pos[1],offset1), pos[1], offset1);

      // Result is from a1
      result_type const s1 = nt2::run ( boost::proto::child_c<1>(a0)
                                      , n1  ? min ( as_index(ex1, pos)
                                                  , bound1
                                                  )
                                            : zi
                                      , t
                                      );

      // Select proper values depending on quadrant informations
      return nt2::if_else ( is_stack0
                          , nt2::if_else(is_row0, s0, z)
                          , nt2::if_else(!is_row0, s1, z)
                          );
    }
  };
} }

#endif
