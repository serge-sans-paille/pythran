//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_2_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_2_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_less_
                          , (typename A0)
                          , bs::sse4_2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE   as_logical_t<A0> operator() ( const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return _mm_cmpgt_epi64(a1,a0);
    }
  };

} } }

#endif
