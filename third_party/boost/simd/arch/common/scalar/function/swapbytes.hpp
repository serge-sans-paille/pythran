//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SWAPBYTES_HPP_INCLUDED

#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( swapbytes_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints8_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const & a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( swapbytes_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints16_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const & a0) const BOOST_NOEXCEPT
    {
      return shift_left(a0, 8)|shr(a0, 8);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( swapbytes_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type32_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const & a0) const BOOST_NOEXCEPT
    {
      A0 val = ((shift_left(a0, 8) & 0xFF00FF00 ) | (shr(a0, 8) & 0xFF00FF ));
      return shift_left(val, 16) | shr(val,16);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( swapbytes_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type64_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const & a0) const BOOST_NOEXCEPT
    {
      A0 val = (shift_left(a0, 8) & 0xFF00FF00FF00FF00ULL ) | (shr(a0, 8) & 0x00FF00FF00FF00FFULL );
      val = (shift_left(val, 16) & 0xFFFF0000FFFF0000ULL ) | (shr(val, 16) & 0x0000FFFF0000FFFFULL );
      return shift_left(val, 32) | shr(val,32);
    }
  };
} } }


#endif
