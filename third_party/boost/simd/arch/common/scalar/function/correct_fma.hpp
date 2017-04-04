//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CORRECT_FMA_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/sign.hpp>
#include <boost/simd/function/two_add.hpp>
#include <boost/simd/function/two_prod.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/config.hpp>
#include <cmath>
#include <tuple>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( fma_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::single_<A0> >
                          , bd::scalar_< bd::single_<A0> >
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const pedantic_tag &
                                     , A0 a0, A0 a1, A0 a2) const BOOST_NOEXCEPT
    {
      return static_cast<A0>( static_cast<double>(a0)*static_cast<double>(a1)
                              + static_cast<double>(a2)
                            );
    }
  };
  BOOST_DISPATCH_OVERLOAD ( fma_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const pedantic_tag &
                                     , A0 a0, A0 a1, A0 a2) const BOOST_NOEXCEPT
    {
      A0 p, rp, s, rs;
    #ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
      using iA0 = bd::as_integer_t<A0>;
      iA0 e0 = exponent(a0);
      iA0 e1 = exponent(a1);
      iA0 e = -bs::max(e0, e1)/2;
      A0 ae2  = ldexp(a2, e);
      auto choose = (e0 > e1);
      A0 amax = choose ? ldexp(a0, e) : ldexp(a1, e);
      A0 amin = choose ? a1 : a0;
      std::tie(p, rp) = two_prod(amax, amin);
      std::tie(s, rs) = two_add(p, ae2);
      return ldexp(s+(rp+rs), -e);
    #else
      std::tie(p, rp) = two_prod(a0, a1);
      std::tie(s, rs) = two_add(p, a2);
      return s+(rp+rs);
    #endif
    }
  };
  BOOST_DISPATCH_OVERLOAD ( fma_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const pedantic_tag &
                                     , A0 a0, A0 a1, A0 a2) const BOOST_NOEXCEPT
    {
      // correct fma has to ensure "no intermediate overflow".
      // This is done in the case of signed integers by transtyping to unsigned type
      // to perform the computations in a guaranted 2-complement environment
      // since signed integer overflows in C++ produce "undefined results"
      using u_t = bd::as_integer_t<A0, unsigned>;
      return A0(fma(u_t(a0), u_t(a1), u_t(a2)));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( fma_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::uint_<A0> >
                          , bd::scalar_< bd::uint_<A0> >
                          , bd::scalar_< bd::uint_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const pedantic_tag &
                                     , A0 a0, A0 a1, A0 a2) const BOOST_NOEXCEPT
    {
      return multiplies(a0, a1)+a2;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( fma_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0 a0, A0 a1, A0 a2) const BOOST_NOEXCEPT
    {
      return std::fma(a0, a1, a2);
    }
  };
} } }


#endif
