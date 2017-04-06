//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITWISE_NOTAND_HPP_INCLUDED

#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/complement.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( bitwise_notand_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          , bd::scalar_< bd::bool_<A1> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return a1 & !a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF( bitwise_notand_
                            , (typename A0, typename A1)
                            , (detail::same_sizeof<A0,A1>)
                            , bd::cpu_
                            , bd::scalar_< bd::arithmetic_<A0> >
                            , bd::scalar_< bd::arithmetic_<A1> >
                            )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1
                                    ) const BOOST_NOEXCEPT
    {
      return bitwise_and(complement(a0), a1);
    }
  };
} } }


#endif
