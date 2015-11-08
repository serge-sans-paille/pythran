//==============================================================================
//         Copyright 2014        LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014        LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_FAST_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_FAST_TOINT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/arithmetic/functions/fast_toint.hpp>
#include <boost/simd/include/functions/simd/split_low.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_toint_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_< double_<A0>
                                             , boost::simd::tag::sse_
                                             >
                                       ))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    typedef typename dispatch::meta::downgrade<result_type>::type int_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const int_type out = _mm_cvttpd_epi32(a0);
      return boost::simd::split_low(out);
    }
  };
} } }

#endif
#endif


