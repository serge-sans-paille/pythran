//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_ALL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_ALL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/reduction/functions/all.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::all_, boost::simd::tag::sse2_,
                              (A0),
                              ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return result_type(_mm_movemask_epi8(genmask(a0)) == 0xFFFF);
    }
  };
} } }

#endif
#endif
