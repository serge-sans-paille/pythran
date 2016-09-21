//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_IMAG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_IMAG_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( is_imag_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return !a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_imag_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return is_eqz(a0);
    }
  };
} } }


#endif
