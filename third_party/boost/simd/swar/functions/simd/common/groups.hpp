//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUPS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUPS_HPP_INCLUDED

#include <boost/simd/swar/functions/groups.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/functions/simd/saturate.hpp>
#include <boost/simd/include/functions/simd/slice.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::groups_
                                    , tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::downgrade<typename A0::value_type>::type base_t;
    typedef typename simd::meta::vector_of< base_t
                                          , A0::static_size
                                          >::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return eval(a0, boost::is_same<A0, result_type>());
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const& a0, boost::mpl::false_ const&) const
    {
      return eval2(a0, boost::mpl::bool_<(A0::static_size>=4)>());
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const& a0, boost::mpl::true_ const&) const
    {
      return a0;
    }

    BOOST_FORCEINLINE
    result_type eval2(A0 const& a0, boost::mpl::true_ const&) const
    {
      typename simd::meta::vector_of< typename A0::value_type
                                    , A0::static_size/2
                                    >::type a00,a01;
      boost::simd::slice(a0,a00,a01);
      return boost::simd::groups(a00,a01);
    }

    BOOST_FORCEINLINE
    result_type eval2(A0 const& a0, boost::mpl::false_ const&) const
    {
      return make<result_type>( groups( extract<0>(a0) )
                              , groups( extract<1>(a0) )
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::groups_, tag::cpu_
                                       , (A0)(X)
                                       , (boost::mpl::not_< boost::is_same<A0
                                                          , typename dispatch::meta::downgrade<A0
                                                          >::type> >)
                                       , ((simd_<arithmetic_<A0>,X>))
                                         ((simd_<arithmetic_<A0>,X>))
                                       )
  {

    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return group(saturate<result_type>(a0), saturate<result_type>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::groups_, tag::cpu_
                                       , (A0)(X)
                                       , (boost::mpl::not_< boost::is_same<A0
                                                          , typename dispatch::meta::downgrade<A0
                                                          >::type> >)
                                       , ((simd_<floating_<A0>,X>))
                                         ((simd_<floating_<A0>,X>))
                                       )
  {

    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return group(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::groups_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::downgrade<typename A0::value_type>::type base_t;
    typedef typename simd::meta::vector_of< base_t
                                          , A0::static_size
                                          >::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return group(a0);
    }
  };
} } }

#endif
