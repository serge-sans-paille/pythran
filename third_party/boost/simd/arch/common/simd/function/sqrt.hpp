//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SQRT_HPP_INCLUDED

#include <boost/simd/function/raw.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/rsqrt.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( sqrt_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      A0 r = if_else_zero(a0, a0 * raw_(rsqrt)(a0));
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(a0 == Inf<A0>(), Inf<A0>(), r);
      #else
      return r;
      #endif
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( sqrt_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bs::pack_< bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( bs::assert_all(is_positive(a0))
                      , "sqrt integer domain is restricted to positive integer."
                      );
      return sqrt(a0);
    }
  };
} } }

#endif
