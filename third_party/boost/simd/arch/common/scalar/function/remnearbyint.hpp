//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMNEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMNEARBYINT_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/div.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// The remnearbyint() function computes the remnearbyint of dividing x by y.  The
// return value is x-n*y, where n is the value x / y, rounded to the nearest
// integer.  If the boost::simd::absolute value of x-n*y is 0.5, n is chosen
// to be even.
/////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::nearbyint_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    ,bd::functor<bs::tag::nearbyint_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1))
        return fnms(div(nearbyint, a0, a1), a1, a0);
      else
        return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::nearbyint_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    ,bd::functor<bs::tag::nearbyint_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1)&&is_eqz(a0)) return a0;
      return  fnms(div(nearbyint, a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::nearbyint_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::nearbyint_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(div(nearbyint, a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::nearbyint_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::nearbyint_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(div(nearbyint, a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bs::tag::nearbyint_
                          , bd::scalar_< bd::signed_<A0> >
                          , bd::scalar_< bd::signed_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    , bd::functor<bs::tag::nearbyint_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return std::remainder(a0, a1);
    }
  };
} } }

#endif
