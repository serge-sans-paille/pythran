//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_GROUP_HPP_INCLUDED

#include <boost/simd/swar/functions/group.hpp>
#include <boost/simd/include/functions/simd/deinterleave_first.hpp>
#include <boost/simd/include/functions/simd/deinterleave_second.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/slice.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/endian.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::group_
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
      return boost::simd::group(a00,a01);
    }

    BOOST_FORCEINLINE
    result_type eval2(A0 const& a0, boost::mpl::false_ const&) const
    {
      return make<result_type>( static_cast<base_t>( extract<0>(a0) )
                              , static_cast<base_t>( extract<1>(a0) )
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::group_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::mpl::not_
                                          < boost::is_same
                                            < A0
                                            , typename dispatch::meta::downgrade<A0>::type
                                            >
                                          >
                                        )
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A0>,X>))
                                      )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      static const size_t size = boost::simd::meta::cardinal_of<A0>::value;
      typedef typename meta::scalar_of<result_type>::type sR;
      result_type that;
      for(size_t i = 0; i != size; ++i)
        that[i]      = static_cast<sR>(a0[i]);
      for(size_t i = 0; i != size; ++i)
        that[i+size] = static_cast<sR>(a1[i]);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::group_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::mpl::not_
                                          < boost::is_same
                                            < A0
                                            , typename dispatch::meta::downgrade<A0>::type
                                            >
                                          >
                                        )
                                      , ((simd_<integer_<A0>,X>))
                                        ((simd_<integer_<A0>,X>))
                                      )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      #ifdef BOOST_LITTLE_ENDIAN
      return deinterleave_first(bitwise_cast<result_type>(a0), bitwise_cast<result_type>(a1));
      #else
      return deinterleave_second(bitwise_cast<result_type>(a0), bitwise_cast<result_type>(a1));
      #endif
    }
  };
} } }
#endif
