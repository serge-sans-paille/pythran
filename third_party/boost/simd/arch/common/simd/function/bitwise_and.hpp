//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_AND_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( bitwise_and_
                            , (typename A0, typename A1, typename X, typename Y)
                            , (nsm::and_< nsm::not_ < std::is_same<A0,A1> >
                                            , nsm::and_ < detail::is_native<X>
                                                            , detail::is_native<Y>
                                                            >
                                            >
                              )
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            , bs::pack_<bd::arithmetic_<A1>,Y>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A1& a1 ) const BOOST_NOEXCEPT
    {
      return bitwise_and(a0, simd::bitwise_cast<A0>(a1));
    }
  };
 } } }

#endif

