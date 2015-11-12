//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_CONTAINER_SPLIT_MULTIPLIES_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_CONTAINER_SPLIT_MULTIPLIES_HPP_INCLUDED

#include <nt2/swar/functions/split_multiplies.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/comparison.hpp>

#if 0
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/bitwise_and.hpp>
#endif

namespace nt2 { namespace ext
{
// can't statically know we have enough data for split
#if 0
  // split
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , (mpl::greater< mpl::sizeof_<typename A0::value_type>
                                           , mpl::sizeof_<typename boost::proto::result_of::child_c<A0&, 0>::value_type::value_type>
                                           >
                              )
                            , ((node_<A0, nt2::tag::split_multiplies_, boost::mpl::long_<2> , nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename Data::type rvec;
    typedef typename meta::downgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      rvec r0, r1;
      nt2::split_multiplies( nt2::run(boost::proto::child_c<0>(a0), p, meta::as_<vec>())
                           , nt2::run(boost::proto::child_c<1>(a0), p, meta::as_<vec>())
                           , r0
                           , r1
                           );

      return if_else(p & meta::cardinal_of<vec>::value-1, r1, r0);
    }
  };
#endif

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::split_multiplies_, boost::mpl::long_<2> , nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      typedef typename boost::proto::result_of::child_c<A0&, 0>::value_type child0;
      typedef typename boost::proto::result_of::child_c<A0&, 1>::value_type child1;
      return nt2::multiplies( nt2::splat<result_type>(nt2::run(boost::proto::child_c<0>(a0), p, boost::simd::ext::adapt_data<child0, Data>::call(data)))
                            , nt2::splat<result_type>(nt2::run(boost::proto::child_c<1>(a0), p, boost::simd::ext::adapt_data<child1, Data>::call(data)))
                            );
    }
  };
} }

#endif
