//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MODF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MODF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/trunc.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<A0>>
                          )
  {
    using result_t = std::pair <A0, A0>;
    BOOST_FORCEINLINE result_t operator()(A0 const& a0) const
    {
      A0 rounded = bs::trunc(a0);
      A0 rest    = a0-rounded;
      return result_t(rest, rounded);
    }
   };

  BOOST_DISPATCH_OVERLOAD ( modf_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_<bd::arithmetic_<A0>>
                          )
  {
    using result_t = std::pair <A0, A0>;
    BOOST_FORCEINLINE result_t operator()(const std_tag &,A0 const& a0) const
    {
      A0 rounded, rest;
      rest = std::modf(a0,&rounded);
      return result_t(rest, rounded);
    }
   };
} } }

#endif
