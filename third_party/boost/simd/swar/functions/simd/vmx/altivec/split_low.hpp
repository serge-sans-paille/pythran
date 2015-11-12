//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SPLIT_LOW_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/split_low.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/dispatch/meta/as_signed.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < int8_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return vec_unpackh( a0() );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < uint8_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      typedef typename dispatch::meta::as_signed<A0>::type      s_t;
      typedef typename dispatch::meta::upgrade<A0,signed>::type sr_t;
      typedef typename result_type::value_type                  r_t;

      sr_t that = vec_unpackh( bitwise_cast<s_t>(a0)() );
      return  bitwise_cast<result_type>(that) & r_t(0x00FF);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < int16_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return vec_unpackh( a0() );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < uint16_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      typedef typename dispatch::meta::as_signed<A0>::type      s_t;
      typedef typename dispatch::meta::upgrade<A0,signed>::type sr_t;
      typedef typename result_type::value_type                  r_t;

      sr_t that = vec_unpackh( bitwise_cast<s_t>(a0)() );
      return  bitwise_cast<result_type>(that) & r_t(0x0000FFFF);
    }
  };
} } }

#endif
#endif
