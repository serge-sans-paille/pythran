//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FLOOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  //------------------------------------------------------------------------------------------------
  // Integer cases are no-op
  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const std_tag&, A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  //------------------------------------------------------------------------------------------------
  // FP cases
  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_HAS_FLOORF
      return ::floorf(a0);
    #else
      return std::floor(a0);
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0) const BOOST_NOEXCEPT
    {
      return std::floor(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( floor_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const std_tag&, A0 a0) const BOOST_NOEXCEPT
    {
      return std::floor(a0);
    }
  };
} } }


#endif
