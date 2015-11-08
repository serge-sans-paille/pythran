//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/predicates/functions/is_not_greater_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_not_greater_equal_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<double_<A0>,boost::simd::tag::sse_>))
                         ((simd_<double_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmpnge_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_not_greater_equal_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<single_<A0>,boost::simd::tag::sse_>))
                         ((simd_<single_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmpnge_ps(a0,a1);
    }
  };
} } }
#endif
#endif
