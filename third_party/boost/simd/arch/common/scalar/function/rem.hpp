//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/constant/nan.hpp>
#include <boost/simd/function/div.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_finite.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return a1 ? a0%a1 : a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1)&&is_eqz(a0)) return a0;
      return fnms(div(fix, a0, a1), a1, a0);
    }
  };

   BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename T)
                           , bd::cpu_
                           , bs::pedantic_tag
                           , bs::tag::fix_
                          , bd::scalar_<bd::arithmetic_<T>>
                          , bd::scalar_<bd::arithmetic_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::fix_> const&
                                  , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return pedantic_(rem)(a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(a1, div(fix, a0, a1), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bs::tag::fix_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, bd::functor<bs::tag::fix_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return std::fmod(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::fix_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (bd::functor<bs::tag::fix_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(a1, div(fix, a0, a1), a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
     return std::fmod(a0, a1);
    }
  };
} } }

// Other flavors of rem
#include <boost/simd/arch/common/scalar/function/remround.hpp>
#include <boost/simd/arch/common/scalar/function/remnearbyint.hpp>
#include <boost/simd/arch/common/scalar/function/remfloor.hpp>
#include <boost/simd/arch/common/scalar/function/remceil.hpp>

#endif
