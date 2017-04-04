//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW2_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/is_finite.hpp>
#endif
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( pow2_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const
    {
      return ldexp(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
    #ifndef BOOST_SIMD_NO_INVALIDS
      BOOST_ASSERT_MSG(boost::simd::assert_all(is_finite(a1)),
                       "pow2 is not defined for an invalid second parameter");
    #endif
      return ldexp(a0, bs::toint(a1));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow2_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return ldexp(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return ldexp(One<A0>(), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const  BOOST_NOEXCEPT
    {
    #ifndef BOOST_SIMD_NO_INVALIDS
      BOOST_ASSERT_MSG(boost::simd::assert_all(is_finite(a0)),
                       "pow2 with one parameter is not defined for an invalid entry");
    #endif
      return ldexp(One<A0>(), toint(a0));
    }
  };
} } }


#endif
