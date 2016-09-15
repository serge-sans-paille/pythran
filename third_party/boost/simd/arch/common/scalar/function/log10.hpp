//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG10_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG10_HPP_INCLUDED
#include <boost/simd/function/std.hpp>


#include <boost/simd/arch/common/detail/scalar/logarithm.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      using ui_t = bd::as_integer_t<A0, unsigned>;
      BOOST_ASSERT_MSG( a0 > 0, "log10 is not defined for zero or negative integers." );
      return static_cast<A0>(log10(static_cast<ui_t>(a0)));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint8_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 100u) ? 2 :
             (a0 >= 10u)  ? 1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint16_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 10000u) ? 4 :
             (a0 >= 1000u)  ? 3 :
             (a0 >= 100u)   ? 2 :
             (a0 >= 10u)    ? 1 : 0;
    }

  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint32_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 1000000000u) ? 9 :
             (a0 >= 100000000u) ?  8 :
             (a0 >= 10000000u) ?   7 :
             (a0 >= 1000000u) ?    6 :
             (a0 >= 100000u) ?     5 :
             (a0 >= 10000u) ?      4 :
             (a0 >= 1000u) ?       3 :
             (a0 >= 100u) ?        2 :
             (a0 >= 10u) ?         1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint64_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return(a0 >= 10000000000000000000ull) ? 19 :
            (a0 >= 1000000000000000000ull) ?  18 :
            (a0 >= 100000000000000000ull) ?   17 :
            (a0 >= 10000000000000000ull) ?    16 :
            (a0 >= 1000000000000000ull) ?     15 :
            (a0 >= 100000000000000ull) ?      14 :
            (a0 >= 10000000000000ull) ?       13 :
            (a0 >= 1000000000000ull) ?        12 :
            (a0 >= 100000000000ull) ?         11 :
            (a0 >= 10000000000ull) ?          10 :
            (a0 >= 1000000000ull) ?            9 :
            (a0 >= 100000000ull) ?             8 :
            (a0 >= 10000000ull) ?              7 :
            (a0 >= 1000000ull) ?               6 :
            (a0 >= 100000ull) ?                5 :
            (a0 >= 10000ull) ?                 4 :
            (a0 >= 1000ull) ?                  3 :
            (a0 >= 100ull) ?                   2 :
            (a0 >= 10ull) ?                    1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::log10(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return detail::logarithm<A0,tag::not_simd_type>::log10(a0);
    }
  };
} } }


#endif

