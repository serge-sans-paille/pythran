//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  //------------------------------------------------------------------------------------------------
  //  float --> int32
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bd::target_<bd::scalar_<bd::int32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return _mm_cvttps_epi32(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int32 --> float
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bd::target_<bd::scalar_<bd::single_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return _mm_cvtepi32_ps(a0);
    }
  };
} } }

#endif
