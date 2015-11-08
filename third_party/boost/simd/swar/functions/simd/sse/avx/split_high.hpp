//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HIGH_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/split_high.hpp>
#include <boost/simd/include/functions/simd/combine.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_high_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 1));
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_high_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      typedef typename meta::retarget<A0,tag::sse_>::type ext_t;
      typedef typename meta::retarget<result_type,tag::sse_>::type part_t;

      ext_t  e = _mm256_extractf128_si256(a0, 1);
      part_t ha1;
      part_t ha0 = split(e, ha1);

      return combine(ha0,ha1);
    }
  };
} } }

#endif
#endif
