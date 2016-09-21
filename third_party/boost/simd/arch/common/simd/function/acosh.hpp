//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOSH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOSH_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/constant/oneotwoeps.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/log1p.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( acosh_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        A0 t = dec(a0);
        auto test = is_greater(t,Oneotwoeps<A0>());
        A0 z = if_else(test, a0, t+sqrt(t+t+sqr(t)));
        return if_plus(test, log1p(z), Log_2<A0>());
      }
   };

} } }

#endif
