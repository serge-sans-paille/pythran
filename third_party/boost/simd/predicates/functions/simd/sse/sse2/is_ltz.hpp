//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_LTZ_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_LTZ_HPP_INCLUDED

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/predicates/functions/is_ltz.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_ltz_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type                     result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename boost::dispatch::meta::downgrade<A0>::type  i32type;

      i32type that = _mm_shuffle_epi32( is_ltz(bitwise_cast<i32type>(a0))
                                      , _MM_SHUFFLE(3,3,1,1)
                                      );

      return  bitwise_cast<result_type>(that);
    }
  };
} } }

#endif
#endif
