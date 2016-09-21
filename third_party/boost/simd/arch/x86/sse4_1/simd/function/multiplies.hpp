//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_mullo_epi32(a0, a1);
    }
  };

} } }

#endif
