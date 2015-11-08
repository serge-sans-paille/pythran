//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_POPCNT_HPP_INCLUDED
#include <boost/simd/bitwise/functions/popcnt.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/scalar/lo.hpp>
#include <boost/simd/include/functions/scalar/hi.hpp>
#include <boost/simd/include/functions/scalar/sbits.hpp>
#include <boost/simd/include/constants/digits.hpp>

#ifdef BOOST_MSVC
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::popcnt(boost::simd::sbits(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)
                            , (scalar_< ints8_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return result_type(__popcnt16(int16_t(a0) & 0xFF));
    #else
      return __builtin_popcount(int32_t(a0) & 0xFF);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)
                            , (scalar_< ints16_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt16(a0);
    #else
      return __builtin_popcount(int32_t(a0) & 0xFFFF);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)
                            , (scalar_< ints32_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
    #ifdef BOOST_MSVC
      return __popcnt(a0);
    #else
      return __builtin_popcount(a0);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::popcnt_, tag::cpu_, (A0)
                            , (scalar_< ints64_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
    #if defined BOOST_MSVC && defined _WIN64
      return __popcnt64(a0);
    #elif defined BOOST_MSVC
      return  __popcnt( hi(a0) )
            + __popcnt( lo(a0) );
    #else
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    #endif
    }
  };
} } }

#endif
