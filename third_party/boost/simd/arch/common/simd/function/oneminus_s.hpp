//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ONEMINUS_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ONEMINUS_S_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD_IF ( oneminus_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::signed_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 const& a0
                                    ) const BOOST_NOEXCEPT
    {
      return /*saturated_TODO*/(minus)(One<A0>(), a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( oneminus_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::unsigned_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &,  A0 const& a0
                                    ) const BOOST_NOEXCEPT
    {
      return One<A0>()-simd::min(a0, One<A0>());
    }
  };
} } }


#endif
