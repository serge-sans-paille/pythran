//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_SPLIT_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/interleave_first.hpp>
#include <boost/simd/function/interleave_second.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( split_multiplies_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                         )
  {
    using up_t = bd::upgrade_t<A0>;
    using result_t = std::pair<up_t,up_t>;

    BOOST_FORCEINLINE result_t operator()(const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      up_t lo = _mm_mul_epi32(a0, a1);
      up_t hi = _mm_mul_epi32(_mm_srli_si128(a0, 4), _mm_srli_si128(a1, 4));
      return { interleave_first(lo, hi), interleave_second(lo, hi) };
    }
  };
} } }

#endif
