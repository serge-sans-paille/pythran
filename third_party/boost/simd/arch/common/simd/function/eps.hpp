//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EPS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EPS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/constant/mindenormal.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/smallestposval.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( eps_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const&) const BOOST_NOEXCEPT
    {
      return A0(1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( eps_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::floating_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a00) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0>;
      using sA0 = typename A0::value_type;

      A0    a = boost::simd::abs(a00);
      auto e1 = exponent(a)-Nbmantissabits<A0>();
      A0    e =  bitwise_cast<A0>(bitwise_cast<iA0>(A0(1))+(shift_left(e1,Nbmantissabits<sA0>())));

#ifndef BOOST_SIMD_NO_DENORMALS
      return if_plus( is_invalid(a)
                    , if_else(a < Smallestposval<A0>(), Mindenormal<A0>(), e)
                    , Nan<A0>()
                    );
#else
      return if_nan_else(is_invalid(a), e);
#endif
    }
  };
} } }

#endif
