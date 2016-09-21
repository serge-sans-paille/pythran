//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SINCPI_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SINCPI_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/invpi.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/sinpi.hpp>

#if !defined(BOOST_SIMD_NO_DENORMALS)
#include <boost/simd/constant/eps.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_less.hpp>
#endif

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_inf.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( sincpi_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        A0 r1 = bs::Invpi<A0>()*(bs::sinpi(a0)/a0);
        #if !defined(BOOST_SIMD_NO_DENORMALS)
        r1 = bs::if_else ( bs::is_less(bs::abs(a0), bs::Eps<A0>())
                          , bs::One<A0>()
                          , r1
                          );
        #else
        r1 = bs::if_else(bs::is_eqz(a0), bs::One<A0>(), r1);
        #endif
        #if !defined(BOOST_SIMD_NO_INFINITIES)
        r1 = bs::if_zero_else(bs::is_inf(a0), r1);
        #endif
        return r1;
      }
   };

} } }

#endif
