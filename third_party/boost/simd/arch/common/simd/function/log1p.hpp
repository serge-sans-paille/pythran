//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG1P_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/if_plus.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF ( log1p_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) BOOST_NOEXCEPT
    {
      A0 u = inc(a0);
      A0 r = if_plus(is_nez(u),
                    log(u),
                    (a0-dec(u))/u); // cancels errors with IEEE arithmetic
#ifndef BOOST_SIMD_NO_INFINITIES
      r = if_else(is_equal(u, Inf<A0>()),u, r);
#endif
      return r;
    }
  };
} } }

#endif
