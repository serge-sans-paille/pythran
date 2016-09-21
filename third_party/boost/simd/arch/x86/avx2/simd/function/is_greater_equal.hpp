//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_IS_GREATER_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/logical_not.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( is_greater_equal_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>
      operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return !(a1 > a0);
      }
   };
} } }

#endif
