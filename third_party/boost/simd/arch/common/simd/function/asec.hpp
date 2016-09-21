//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASEC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/function/acsc.hpp>
#include <boost/simd/function/minus.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( asec_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::double_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      A0 tmp =  (Pio_2<A0>()-acsc(a0)) +  Constant<A0, 0x3c91a62633145c07ll>();
      return if_zero_else(is_equal(a0, One<A0>()), tmp);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( asec_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return (bs::Pio_2<A0>()-bs::acsc(a0));
      }
   };

} } }

#endif
