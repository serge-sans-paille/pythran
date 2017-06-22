//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_DIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_DIVFLOOR_HPP_INCLUDED

#include <boost/simd/function/definition/floor.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/iceil.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::floor_
                          , bd::scalar_< bd::int64_<A0> >
                          , bd::scalar_< bd::int64_<A0> >
                                    )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (!a0) return  Zero<A0>();
      if(a1)
      {
        A0 q = saturated_(divides)(a0, a1);
        A0 r = a0-q*a1;
        if ((r != Zero<A0>())&&((a0^a1) <= 0)) return saturated_(dec)(q);
        return q;
      }
      else
        return ((a0>0) ? Valmax<A0>() : Valmin<A0>());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::floor_
                          , bd::scalar_< bd::signed_<A0> >
                          , bd::scalar_< bd::signed_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if(a1)
        return static_cast<A0 >(-iceil(-static_cast<double>(a0)/static_cast<double>(a1)));
      else
      {
        return (a0) ? ((a0>0) ? Valmax<A0>() : Valmin<A0>()) : Zero<A0>();
      }
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::floor_
                          , bd::scalar_< bd::unsigned_<A0> >
                          , bd::scalar_< bd::unsigned_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if(a1)
        return saturated_(divides)(a0, a1);
      else
        return (a0) ? Valmax<A0>() : Zero<A0>();
    }
  };

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::floor_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return boost::simd::floor(a0/a1);
    }
  };

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} } }


#endif
