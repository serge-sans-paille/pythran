//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IDIVNEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IDIVNEARBYINT_HPP_INCLUDED

// workaround for "idivnearbyint(a0/a1) in floating scalar mode when a0 is non zero and a1 is zero
// with clang 3.7 and 3.8
// 04/24/2016

#include <boost/predef/compiler.h>

#if BOOST_COMP_CLANG >= BOOST_VERSION_NUMBER(3,7,0)
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/inearbyint.hpp>
#include <boost/simd/function/is_negative.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t =  bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( bd::functor<bs::tag::inearbyint_> const&
                                          , A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      if (a1) return  inearbyint(a0/a1);
      if (!a0) return  Nan<result_t>();
      return is_negative(bitwise_or(a0, a1)) ? Valmin<result_t>() : Valmax<result_t>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::inearbyint_> const&,
                                      A0  a0, A0  a1) const BOOST_NOEXCEPT
    {
      return div(nearbyint, a0, a1);
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( bd::functor<bs::tag::inearbyint_> const&
                                                      , A0  a0
                                                      , A0  a1) const BOOST_NOEXCEPT
    {
      return inearbyint(a0/a1);
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif
} } }

#endif
#endif
