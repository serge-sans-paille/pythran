//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/group.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Implementation when type A0 is double
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::group_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_movelh_ps(_mm_cvtpd_ps(a0), _mm_cvtpd_ps(a1));
    }
  };
} } }

#endif
#endif
