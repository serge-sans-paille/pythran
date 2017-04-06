//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GROUPS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GROUPS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( group_
                            , (typename A0)
                            , (bd::is_downgradable<A0>)
                            , bs::sse2_
                            , bs::saturated_tag
                            , bs::pack_<bd::int16_<A0>, bs::sse_>
                            , bs::pack_<bd::int16_<A0>, bs::sse_>
                            )
  {
    using result = bd::downgrade_t<A0>;

    BOOST_FORCEINLINE result
    operator()(const saturated_tag&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return _mm_packs_epi16(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( group_
                            , (typename A0)
                            , (bd::is_downgradable<A0>)
                            , bs::sse2_
                            , bs::saturated_tag
                            , bs::pack_<bd::int32_<A0>, bs::sse_>
                            , bs::pack_<bd::int32_<A0>, bs::sse_>
                            )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(const saturated_tag&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return  _mm_packs_epi32(a0, a1);
    }
  };
} } }

#endif
