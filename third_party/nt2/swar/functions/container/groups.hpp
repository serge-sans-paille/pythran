//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_CONTAINER_GROUPS_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_CONTAINER_GROUPS_HPP_INCLUDED

#include <nt2/swar/functions/groups.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/comparison.hpp>

namespace nt2 { namespace ext
{
  // groups
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , (mpl::and_<
                                mpl::less< mpl::sizeof_<typename A0::value_type>
                                         , mpl::sizeof_<typename boost::proto::result_of::child_c<A0&, 0>::value_type::value_type>
                                         >
                              , simd::meta::is_vectorizable<typename boost::proto::result_of::child_c<A0&, 0>::value_type::value_type, X>
                              >)
                            , ((node_<A0, nt2::tag::groups_, boost::mpl::long_<1>, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename Data::type rvec;
    typedef typename meta::upgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, State const& p, Data const&) const
    {
      vec v0, v1;
      v0 = run(boost::proto::child_c<0>(a0), p, meta::as_<vec>());
      v1 = run(boost::proto::child_c<0>(a0), p+meta::cardinal_of<vec>::value, meta::as_<vec>());

      return nt2::groups(v0, v1);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::groups_, boost::mpl::long_<1> , nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      typedef typename boost::proto::result_of::child_c<A0&, 0>::value_type child0;
      return nt2::splat<result_type>(nt2::saturate<result_type>(nt2::run(boost::proto::child_c<0>(a0), p, boost::simd::ext::adapt_data<child0, Data>::call(data))));
    }
  };
} }

#endif
