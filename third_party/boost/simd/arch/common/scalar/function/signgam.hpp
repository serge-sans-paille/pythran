//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGNGAM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGNGAM_HPP_INCLUDED

#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/nan.hpp>

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( signgam_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      if (is_lez(a0))
      {
        if (is_flint(a0))
          return Nan<A0>();
        else
          return One<A0>()-bool(is_odd(floor(a0)))*Two<A0>();
      }
#else
      if (is_lez(a0))
      {
        if (is_flint(a0)||is_inf(a0))
          return Nan<A0>();
        else
          return One<A0>()-bool(is_odd(floor(a0)))*Two<A0>();
      }
      else if (is_nan(a0)) return a0;
#endif
      return One<A0>();
    }
  };
} } }


#endif
