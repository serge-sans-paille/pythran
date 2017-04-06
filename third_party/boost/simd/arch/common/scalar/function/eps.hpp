//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EPS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EPS_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_DENORMALS
#include <limits>
#endif

#include <boost/simd/constant/mindenormal.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( eps_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( A0 ) const BOOST_NOEXCEPT
    {
      return static_cast<A0>(1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( eps_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    A0 operator()(A0 a0) const BOOST_NOEXCEPT
    {
      const A0 a = bs::abs(a0);

            if (is_invalid(a))  return Nan<A0>();
#ifndef BOOST_SIMD_NO_DENORMALS
      else  if (a < std::numeric_limits<A0>::min()) return Mindenormal<A0>();
#endif
      else
      {
        using i_t = bd::as_integer_t<A0, unsigned>;

        i_t e1 = exponent(a)-Nbmantissabits<A0>();
        return bitwise_cast<A0>(bitwise_cast<i_t>(A0(1))+(e1 << Nbmantissabits<A0>()));
      }
    }
  };
} } }


#endif
