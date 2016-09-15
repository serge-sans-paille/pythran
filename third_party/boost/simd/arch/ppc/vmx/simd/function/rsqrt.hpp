//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_RSQRT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/sqr.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( rsqrt_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
      {
        A0 o  = One<A0>();
        A0 estimate = fast_(rsqrt)(a0);
        A0 se = sqr(estimate);
        A0 he = estimate*Half<A0>();
        A0 st = vec_nmsub(a0.storage(),se.storage(),o.storage());
        return fma(st, he, estimate);
      }
   };

   BOOST_DISPATCH_OVERLOAD( rsqrt_
                          , (typename A0)
                          , bs::vmx_
                          , bs::fast_tag
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(bs::fast_tag const&, const A0& a0) const BOOST_NOEXCEPT
      {
        return vec_rsqrte( a0.storage() );
      }
   };
} } }

#endif
