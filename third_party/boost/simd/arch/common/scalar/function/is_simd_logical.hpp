//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( is_simd_logical_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0 == genmask(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_simd_logical_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return is_simd_logical(bitwise_cast<bd::as_integer_t<A0>>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_simd_logical_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<logical_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const&) const BOOST_NOEXCEPT
    {
      return {true};
    }
  };
} } }

#endif
