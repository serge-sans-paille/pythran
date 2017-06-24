//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FMASUBADD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FMASUBADD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/function/fms.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( fmasubadd_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<T>>
                          , bd::scalar_<bd::unspecified_<T>>
                          , bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a, T b, T c) const BOOST_NOEXCEPT
    {
      return fms(a, b, c);
    }
  };
} } }

#endif
