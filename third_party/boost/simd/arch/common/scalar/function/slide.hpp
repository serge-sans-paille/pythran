//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SLIDE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename Value, typename Offset)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    BOOST_FORCEINLINE Value operator()(Value const& a0, Offset const&) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename Value, typename Offset)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    BOOST_FORCEINLINE Value operator()(Value const& a0, Value const&, Offset const&) const
    {
      return a0;
    }
  };
} } }

#endif
