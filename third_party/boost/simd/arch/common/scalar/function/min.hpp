//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MIN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MIN_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/std.hpp>
#include <algorithm>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( min_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return (a1 < a0) ? a1 : a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( min_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( pedantic_tag const&, A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return  (a1 < a0) ? a1 : a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( min_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( std_tag const&, A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return std::min(a0, a1);
    }
  };

} } }


#endif
