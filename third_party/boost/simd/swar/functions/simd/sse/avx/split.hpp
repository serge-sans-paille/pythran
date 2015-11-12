//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_
                                   , tag::cpu_
                                   , (A0)
                                   , (( simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                     ))
                                   )
  {
    typedef typename dispatch::meta::upgrade<typename A0::value_type>::type base_t;
    typedef typename simd::meta::vector_of< base_t
                                          , A0::static_size
                                          >::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return _mm256_cvtps_pd(a0);
    }
  };
} } }

#endif
#endif
