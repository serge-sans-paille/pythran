//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SECH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SECH_HPP_INCLUDED

#include <boost/simd/function/cosh.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( sech_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<A0>, X>
                          )
  {
    using result_t = A0;
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::rec(bs::cosh(a0));
    }
  };
} } }


#endif
