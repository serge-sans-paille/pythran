//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REVERSEBITS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( reversebits_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints8_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return std::uint8_t(
        ((uint8_t(a0) * 0x0802LU & 0x22110LU)
         | (uint8_t(a0) * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16
      );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reversebits_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints64_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      union { A0 a; std::uint32_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reversebits_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints16_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      union { A0 a; std::uint8_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return  z.a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reversebits_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints32_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      union { A0 a; std::uint16_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
    }
  };
} } }


#endif
