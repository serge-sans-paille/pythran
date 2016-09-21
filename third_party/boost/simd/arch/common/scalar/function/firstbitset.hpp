//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FIRSTBITSET_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FIRSTBITSET_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( firstbitset_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, unsigned>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0 & (~a0+One<result_t>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( firstbitset_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, unsigned>;
    result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return firstbitset(bitwise_cast<result_t>(a0));
    }
  };
} } }


#endif
