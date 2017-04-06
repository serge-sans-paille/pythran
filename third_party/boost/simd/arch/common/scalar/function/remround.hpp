//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMROUND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMROUND_HPP_INCLUDED

#include <boost/simd/function/div.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/round.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
/////////////////////////////////////////////////////////////////////////////
// The remround() function computes the remround of dividing x by y.  The
// return value is x-n*y, where n is the value x / y, rounded toward +infinity
/////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::round_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    , bd::functor<bs::tag::round_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1))
        return fnms(div(round, a0, a1), a1, a0);
      else
        return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::tag::round_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (pedantic_tag const &
                                    , bd::functor<bs::tag::round_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nez(a1)&&is_eqz(a0)) return a0;
      return fnms(div(round, a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::round_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::round_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(div(round, a0,a1), a1, a0);
    }
  };

   BOOST_DISPATCH_OVERLOAD ( rem_
                          , (typename A0)
                          , bd::cpu_
                          , bs::tag::round_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( bd::functor<bs::tag::round_> const&
                                    , A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return fnms(div(round, a0,a1), a1, a0);
    }
  };
} } }


#endif
