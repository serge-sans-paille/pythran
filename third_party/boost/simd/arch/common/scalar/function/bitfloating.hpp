//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITFLOATING_HPP_INCLUDED

#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( bitfloating_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<A0> >
                          )
  {
    using result_t = bd::as_floating_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0 >= Zero<A0>() ?
        bitwise_cast<result_t>(a0) :
        bitwise_cast<result_t>(Signmask<A0>()-a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned
  /////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_OVERLOAD ( bitfloating_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::unsigned_<A0> >
                          )
  {
    using result_t = bd::as_floating_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return bitwise_cast<result_t>(a0);
    }
  };
} } }


#endif
