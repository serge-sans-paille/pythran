//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ACOS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ACOS_HPP_INCLUDED

#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD ( acos_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pedantic_tag
                          , bs::pack_< bd::double_<A0>, bs::sse_>
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      return A0(bs::pedantic_(bs::acos)(a0[0]), bs::pedantic_(bs::acos)(a0[1]));
    }
  };
} } }


#endif
