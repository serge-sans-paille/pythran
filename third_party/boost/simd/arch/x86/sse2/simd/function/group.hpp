//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( group_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, sse_>
                          , bs::pack_<bd::double_<A0>, sse_>
                          )
   {
      using result = bd::downgrade_t<A0>;

      BOOST_FORCEINLINE result operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return _mm_movelh_ps(_mm_cvtpd_ps(a0), _mm_cvtpd_ps(a1));
      }
   };

} } }

#include <boost/simd/arch/x86/sse2/simd/function/groups.hpp>

#endif
