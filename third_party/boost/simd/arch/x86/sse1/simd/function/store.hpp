//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( store_
                          , (typename Vec, typename Pointer)
                          , bs::sse1_
                          , bs::pack_<bd::single_<Vec>, bs::sse_>
                          , bd::pointer_<bd::scalar_<bd::single_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      _mm_storeu_ps((float*)(a1),a0);
    }
  };

} } }

#endif
