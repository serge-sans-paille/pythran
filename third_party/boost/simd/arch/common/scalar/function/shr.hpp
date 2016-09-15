//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SHR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SHR_HPP_INCLUDED

#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( shr_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0  operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using uitype = bd::as_integer_t<A0, unsigned>;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shr : shift is out of range");
      return uitype(a0) >> a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shr_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using uitype = bd::as_integer_t<A0, unsigned>;
      return bitwise_cast<A0>(shr(bitwise_cast<uitype>(a0), a1));
    }
  };
} } }


#endif
