//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TOFLOAT_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
 BOOST_DISPATCH_OVERLOAD ( tofloat_
                         , (typename A0)
                         , bd::cpu_
                         , bd::scalar_< bd::arithmetic_<A0> >
                         )
 {
    using result_t = bd::as_floating_t<A0>;
    BOOST_FORCEINLINE result_t operator() (A0 a0) const BOOST_NOEXCEPT
    {
      return static_cast<result_t>(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( tofloat_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }


#endif
