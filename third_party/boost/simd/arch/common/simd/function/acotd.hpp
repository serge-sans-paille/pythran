//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOTD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOTD_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/function/is_inf.hpp>
#endif
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/atand.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( acotd_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      A0 z = Ratio<A0, 90>()-if_else_zero(is_nez(a0),atand(bs::abs(a0)));
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = if_zero_else(is_inf(a0),z);
      #endif
      return bitwise_or(z, bitofsign(a0));
    }
  };
} } }


#endif
