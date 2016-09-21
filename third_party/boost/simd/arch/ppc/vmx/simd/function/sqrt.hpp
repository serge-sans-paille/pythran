//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SQRT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/rsqrt.hpp>

#if !defined(BOOST_SIMD_NO_INVALIDS)
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/if_else.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( sqrt_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
      {
        A0 that = if_else_zero(a0, a0 * rsqrt(a0));
        #if !defined(BOOST_SIMD_NO_INVALIDS)
        return if_else( a0 == Inf<A0>(), a0, that);
        #else
        return that;
        #endif
      }
   };

   BOOST_DISPATCH_OVERLOAD( sqrt_
                          , (typename A0)
                          , bs::vmx_
                          , bs::fast_tag
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(bs::fast_tag const&, const A0& a0) const BOOST_NOEXCEPT
      {
        return if_else_zero(a0, a0 * fast_(rsqrt)(a0));
      }
   };
} } }

#endif
