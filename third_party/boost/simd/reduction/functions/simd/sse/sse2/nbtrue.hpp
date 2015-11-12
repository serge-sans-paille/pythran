//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/reduction/functions/nbtrue.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/popcnt.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Implementation when type A0 is arithmetic_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nbtrue_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type                     result_type;
    typedef typename meta::make_dependent<boost::simd::int8_t,A0>::type   base;
    typedef simd::native<base,boost::simd::tag::sse_>                   i8type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      i8type tmp = bitwise_cast<i8type>(genmask(a0));
      return  result_type(boost::simd::popcnt(_mm_movemask_epi8(tmp))
                          * boost::simd::meta::cardinal_of<A0>::value >> 4);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nbtrue_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type                     result_type;
    typedef typename meta::make_dependent<boost::simd::int8_t,A0>::type   base;
    typedef simd::native<base,boost::simd::tag::sse_>                   i8type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      i8type tmp = bitwise_cast<i8type>(genmask(a0));
      return  result_type(boost::simd::popcnt(_mm_movemask_epi8(tmp))
                          * boost::simd::meta::cardinal_of<A0>::value >> 4);
    }
  };

  //============================================================================
  // Implementation when type A0 is double
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nbtrue_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef double result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      int r = _mm_movemask_pd(genmask(a0));
      return double((r&1)+(r>>1));
    }
  };

  //============================================================================
  // Implementation when type A0 is float
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::nbtrue_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef float result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      int r = _mm_movemask_ps(genmask(a0));
      return float((r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3));
    }
  };
} } }

#endif
#endif
