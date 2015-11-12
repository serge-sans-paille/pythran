//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_RSQRT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_rsqrt.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/rsqrt.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      typedef typename dispatch::meta::as_integer<A0>::type i_t;

      // Quake III Arena RSQRT approximation
      i_t x = bitwise_cast<i_t>(a0);
      i_t y = 0x5f3759df - (x >> 1);

      // make negative values be NaN
      y |= x >> (sizeof(i_t)*CHAR_BIT-1);

      A0 x2 = a0 * 0.5f;
      A0 y2 = bitwise_cast<A0>(y);

      // Newton-Rhapson refinement steps: 2 NR steps for precision purpose
      y2    = y2 * ( 1.5f - ( x2 * y2 * y2 ) );
      return  y2 * ( 1.5f - ( x2 * y2 * y2 ) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rsqrt_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return simd::rsqrt(a0);
    }
  };
} } }

#endif
