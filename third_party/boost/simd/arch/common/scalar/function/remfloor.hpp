//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMFLOOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/function/div.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// The remfloor() function computes the remfloor of dividing x by y.  The
// return value is x-n*y, where n is the value x / y, rounded toward -infinity
/////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::floor_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    ,bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1))
        return fnms(div(floor, a0, a1), a1, a0);
      else
        return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::floor_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(div(floor, a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
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
      return  fnms(div(floor, a0,a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::floor_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    , bd::functor<bs::tag::floor_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1)&&is_eqz(a0)) return a0;
      return fnms(div(floor, a0, a1), a1, a0);
    }
  };
} } }

#endif
