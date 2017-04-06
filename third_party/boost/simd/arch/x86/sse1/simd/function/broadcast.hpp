//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::sse1_
                          , bs::pack_<bd::single_<A0>,bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return do_(a0,nsm::bool_<(A1::value >= 0 && A1::value < 4)>{});
    }

    static BOOST_FORCEINLINE A0 do_(A0 const& a0, nsm::bool_<true> const&) BOOST_NOEXCEPT
    {
      return _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(A1::value,A1::value,A1::value,A1::value));
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };
} } }

#endif
