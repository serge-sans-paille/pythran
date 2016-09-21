//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bd::scalar_< bd::unspecified_<T>>
                          ,  bd::scalar_< bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE auto operator()(T const& a, T const& b) const BOOST_NOEXCEPT -> decltype(a*b)
    {
      return a*b;
    }
  };

   BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bd::scalar_< bd::fundamental_<T>>
                          ,  bd::scalar_< bd::fundamental_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return a*b;
    }
  };
} } }

#include <boost/simd/arch/common/scalar/function/multiplies_s.hpp>

#endif
