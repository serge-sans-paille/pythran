//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SUM_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/splatted.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::arithmetic_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return sum(slice_low(a0)+slice_high(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx_
                          , bs::splatted_tag
                          , bs::pack_<bd::arithmetic_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(bs::splatted_tag const&, const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return A0(sum(a0));
    }
  };
} } }

#endif
