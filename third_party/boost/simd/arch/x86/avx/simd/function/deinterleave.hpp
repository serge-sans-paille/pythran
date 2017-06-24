//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_DEINTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_DEINTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/deinterleave_first.hpp>
#include <boost/simd/function/deinterleave_second.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <array>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::fundamental_<A0>, bs::avx_>
                          , bs::pack_<bd::fundamental_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1 ) const BOOST_NOEXCEPT
    {
      auto s00 = slice_low(a0), s01 = slice_high(a0);
      auto s10 = slice_low(a1), s11 = slice_high(a1);

      auto f = combine(deinterleave_first (s00,s01), deinterleave_first (s10,s11));
      auto s = combine(deinterleave_second(s00,s01), deinterleave_second(s10,s11));

      std::array<A0,2> that{f,s};
      return that;
    }
  };
} } }

#endif
