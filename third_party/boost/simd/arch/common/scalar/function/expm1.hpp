//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPM1_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPM1_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/arch/common/detail/generic/expm1_kernel.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/logeps.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( expm1_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      using sA0 = bd::scalar_of_t<A0>;
    #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0)) return Nan<A0>();
    #endif
      if((a0 < Logeps<A0>())) return Mone<A0>();
      if((a0 > Maxlog<A0>())) return  Inf<A0>();
      return detail::expm1_kernel<A0, sA0>::expm1(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( expm1_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::expm1(a0);
    }
  };
} } }


#endif
