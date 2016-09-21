
//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SIGN_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SIGN_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_sign_epi32(One<A0>(), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_sign_epi8(One<A0>(), a0);
    }
  };
   BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bs::ssse3_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_sign_epi16(One<A0>(), a0);
    }
  };

} } }

#endif
