//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMPROD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMPROD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/cumprod.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumprod_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint o = simd::bitwise_cast<sint>(One<A0>());
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_or_si128(_mm_slli_si128(tmp,1), _mm_srli_si128(o,15));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,2), _mm_srli_si128(o,14));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,3), _mm_srli_si128(o,13));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,4), _mm_srli_si128(o,12));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,5), _mm_srli_si128(o,11));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,6), _mm_srli_si128(o,10));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,7), _mm_srli_si128(o,9));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,8), _mm_srli_si128(o,8));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,9), _mm_srli_si128(o,7));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,10), _mm_srli_si128(o,6));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,11), _mm_srli_si128(o,5));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,12), _mm_srli_si128(o,4));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,13), _mm_srli_si128(o,3));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,14), _mm_srli_si128(o,2));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,15), _mm_srli_si128(o,1));
      return a*simd::bitwise_cast<A0>(tmp1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumprod_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      sint o = simd::bitwise_cast<sint>(One<A0>());
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_or_si128(_mm_slli_si128(tmp,8), _mm_srli_si128(o,8));
      return a0*simd::bitwise_cast<A0>(tmp1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumprod_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint o = simd::bitwise_cast<sint>(One<A0>());
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_or_si128(_mm_slli_si128(tmp,2), _mm_srli_si128(o,14));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,4), _mm_srli_si128(o,12));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp, 6), _mm_srli_si128(o,10));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,8), _mm_srli_si128(o,8));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,10), _mm_srli_si128(o,6));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,12), _mm_srli_si128(o,4));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp,14), _mm_srli_si128(o,2));
      return a*simd::bitwise_cast<A0>(tmp1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumprod_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      A0 a = a0;
      sint o = simd::bitwise_cast<sint>(One<A0>());
      sint tmp = simd::bitwise_cast<sint>(a0);
      sint tmp1 = _mm_or_si128(_mm_slli_si128(tmp, 4), _mm_srli_si128(o,12));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp, 8), _mm_srli_si128(o,8));
      a = a*simd::bitwise_cast<A0>(tmp1);
      tmp1 = _mm_or_si128(_mm_slli_si128(tmp, 12), _mm_srli_si128(o,4));
      return a*simd::bitwise_cast<A0>(tmp1);
    }
  };

} } }
#endif
#endif
