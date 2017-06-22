//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SUBADD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SUBADD_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( subadd_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<T>>
                          , bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a, T b) const BOOST_NOEXCEPT
    {
      return a - b;
    }
  };
} } }

#endif
