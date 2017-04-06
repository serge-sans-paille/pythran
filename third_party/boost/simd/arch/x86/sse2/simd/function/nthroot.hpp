//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/nthroot.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( nthroot_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A1>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      return {nthroot(a0[0], a1[0]), nthroot(a0[1], a1[1])};
    }
  };
  BOOST_DISPATCH_OVERLOAD ( nthroot_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::raw_tag
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::ints64_<A1>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( raw_tag const&,
                                      const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      return {bs::raw_(nthroot)(a0[0], a1[0]), bs::raw_(nthroot)(a0[1], a1[1])};

    }
  };

} } }

#endif
