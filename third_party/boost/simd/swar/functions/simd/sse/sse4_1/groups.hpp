//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUPS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUPS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/swar/functions/groups.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::groups_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_packus_epi32( (a0 & 0x7FFFFFFF) | shri(a0 & 0xF0000000, 1)
                             , (a1 & 0x7FFFFFFF) | shri(a1 & 0xF0000000, 1)
                             );
    }
  };
} } }

#endif
#endif
