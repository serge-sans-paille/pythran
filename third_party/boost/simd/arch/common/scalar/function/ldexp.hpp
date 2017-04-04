//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LDEXP_HPP_INCLUDED
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/std.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/detail/constant/minexponent.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#endif
#include <boost/simd/detail/constant/limitexponent.hpp>
#include <boost/simd/detail/constant/maxexponent.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  // a0 a1 integers
  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return (a1>0)?(a0<<a1):(a0>>a1);
    }
  };

  // a0 floating
  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &
                                    ,  A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      i_t e =  a1;
      A0 f = One<A0>();
    #ifndef BOOST_SIMD_NO_DENORMALS
      if (BOOST_UNLIKELY((e < Minexponent<A0>())))
      {
        e -= Minexponent<A0>();
        f = Smallestposval<A0>();
      }
    #endif
      i_t b = (e == Limitexponent<A0>());
      f += A0(b);
      e -= b;
      e += Maxexponent<A0>();
      e = shift_left(e, Nbmantissabits<A0>());
      return a0*bitwise_cast<A0>(e)*f;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &
                                    , A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return bs::ldexp(a0, a1);
    }
  };

  // a0 floating
  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      i_t ik =  a1+Maxexponent<A0>();
      ik = shift_left(ik, Nbmantissabits<A0>());
      return a0*bitwise_cast<A0>(ik);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0 a0, A1 a1 ) const BOOST_NOEXCEPT
    {
      return std::ldexp(a0, a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0 a0, A1 a1 ) const BOOST_NOEXCEPT
    {
      return bs::ldexp(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0 a0, A1 a1 ) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_flint(a1)||is_invalid(a1), "parameter is not a flint nor is invalid");
      return std::ldexp(a0, toint(a1));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ldexp_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0, A1 a1 ) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_flint(a1)||is_invalid(a1), "parameter is not a flint nor is invalid");
      return std::ldexp(a0, toint(a1));
    }
  };
} } }


#endif
