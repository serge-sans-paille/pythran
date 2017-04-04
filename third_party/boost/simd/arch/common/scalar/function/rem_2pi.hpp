//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_2PI_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_2PI_HPP_INCLUDED

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/inv2pi.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/detail/constant/pix2_1.hpp>
#include <boost/simd/detail/constant/pix2_2.hpp>
#include <boost/simd/detail/constant/pix2_3.hpp>
#include <boost/simd/constant/threeeps.hpp>
#include <boost/simd/constant/twopi.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/rem_pio2.hpp>
#include <boost/simd/function/rem_pio2_medium.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD (rem_2pi_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_ < bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      A0 xr;
      i_t n;
      std::tie(n, xr) = rem_pio2(a0);
      xr += tofloat(n)*Pio_2<A0>();
      return ((xr > Pi<A0>())? xr-Twopi<A0>(): xr);
    }

  };

  BOOST_DISPATCH_OVERLOAD (rem_2pi_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_ <bd::floating_<A0> >
                          , bd::target_ <bd::unspecified_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 const&) const BOOST_NOEXCEPT
    {
      typedef typename A1::type selector;
      return rem2pi<selector, void>::rem(a0);
    }

    template < class T, class dummy = void> struct rem2pi
    {
      static BOOST_FORCEINLINE A0 rem( A0 const&, A0 &, A0&) BOOST_NOEXCEPT
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_2pi");
      }
    };
    template < class dummy> struct rem2pi < tag::big_tag, dummy>
    {
      static BOOST_FORCEINLINE A0 rem( A0 x) BOOST_NOEXCEPT
      {
        return rem_2pi(x);
      }
    };
    template < class dummy> struct rem2pi < tag::very_small_tag, dummy > // |a0| <2*pi
    {
      static BOOST_FORCEINLINE A0 rem( A0 x) BOOST_NOEXCEPT
      {
        return (is_greater(x, Pi<A0>())? x-Twopi<A0>(): (is_less(x, -Pi<A0>())? x+Twopi<A0>(): x));
      }
    };
    template < class dummy> struct rem2pi < tag::small_tag, dummy >// |a0| <= 20*pi
    {
      static BOOST_FORCEINLINE A0 rem( A0 x) BOOST_NOEXCEPT
      {
        A0 xi =  nearbyint(x*Inv2pi<A0>());
        A0 xr = x-xi*Pix2_1<A0>();
        xr -= xi*Pix2_2<A0>();
        xr -= xi*Pix2_3<A0>();
        return xr;
      }
    };

    template < class dummy> struct rem2pi < tag::medium_tag, dummy >
    {
      static BOOST_FORCEINLINE A0 rem( A0 x) BOOST_NOEXCEPT
      {
        using i_t = bd::as_integer_t<A0>;
        A0 xr;
        i_t n = rem_pio2_medium(x, xr);
        xr += tofloat(n)*Pio_2<A0>();
        xr = (is_greater(xr, Pi<A0>())? xr-Twopi<A0>(): xr);
        return xr;
      }
    };
  };
} } }


#endif
