//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXPM1_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXPM1_HPP_INCLUDED

#include <boost/simd/constant/logeps.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/arch/common/detail/generic/expm1_kernel.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( expm1_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const BOOST_NOEXCEPT
    {
      using sA0 = bd::scalar_of_t<A0>;
      return if_else(is_less(a0, Logeps<A0>()),
                     Mone<A0>(),
                     if_else(is_greater(a0, Maxlog<A0>()),
                             Inf<A0>(),
                              detail::expm1_kernel<A0, sA0>::expm1(a0)
                            )
                    );
    }
  };
} } }

#endif
