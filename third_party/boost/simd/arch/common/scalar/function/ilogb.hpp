//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOGB_HPP_INCLUDED

#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0 ) const BOOST_NOEXCEPT
    {
      return static_cast<A0>(bs::ilogb(static_cast<bd::as_floating_t<A0>>(a0)));
    }
  };


  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() (const std_tag &, A0 a0 ) const BOOST_NOEXCEPT
    {
      return std::ilogb(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() (const pedantic_tag &, A0 a0 ) const BOOST_NOEXCEPT
    {
      return std::ilogb(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() (A0 a0 ) const BOOST_NOEXCEPT
    {
      return is_inf(a0) ? Valmax<result_t>() : exponent(a0);
    }
  };

} } }


#endif
