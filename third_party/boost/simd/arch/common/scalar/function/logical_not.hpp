//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOGICAL_NOT_HPP_INCLUDED

#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( logical_not_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return !a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( logical_not_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bs::logical_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return !a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( logical_not_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE auto operator()(T const& a) const BOOST_NOEXCEPT -> decltype(!a)
    {
      return !a;
    }
  };
} } }


#endif
