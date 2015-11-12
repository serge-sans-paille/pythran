//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMSUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/cumsum.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_slli_si128(tmp,1);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,2);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,3);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,4);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,5);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,6);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,7);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,8);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,9);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,10);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,11);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,12);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,13);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,14);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 15);
      a += simd::bitwise_cast<A0>(tmp1);
      return a;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_slli_si128(tmp,8);
      return a0+simd::bitwise_cast<A0>(tmp1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_slli_si128(tmp,2);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,4);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 6);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,8);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,10);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,12);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp,14);
      return a+simd::bitwise_cast<A0>(tmp1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_slli_si128(tmp, 4);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 8);
      a = a+simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_slli_si128(tmp, 12);
      return a+simd::bitwise_cast<A0>(tmp1);
    }
  };
} } }
#endif
#endif
