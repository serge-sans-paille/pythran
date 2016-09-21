//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( if_zero_else_one_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< logical_<A0> >
                          )
  {
    using result_t = typename A0::value_type;
    BOOST_FORCEINLINE result_t operator() ( A0  a0) const BOOST_NOEXCEPT
    {
      return a0 ? Zero<result_t>() : One<result_t>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( if_zero_else_one_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0  a0) const BOOST_NOEXCEPT
    {
      return  A0(a0 == boost::simd::Zero<A0>());
    }
  };

//   BOOST_DISPATCH_OVERLOAD ( if_zero_else_one_
//                           , (typename A0)
//                           , bd::cpu_
//                           , bd::scalar_< bd::fundamental_<A0> >
//                           )
//   {
//     BOOST_FORCEINLINE A0 operator() ( A0  a0) const BOOST_NOEXCEPT
//     {
//       return  a0 ? Zero<A0>() : One<A0>();
//     }
//   };

  BOOST_DISPATCH_OVERLOAD ( if_zero_else_one_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0  a0) const BOOST_NOEXCEPT
    {
      return !a0;
    }
  };
} } }


#endif
