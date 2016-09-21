//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TRUNC_HPP_INCLUDED
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/fast.hpp>

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {


    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return bitwise_or(floor(bs::abs(a0)), bitofsign(a0));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::floating_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return static_cast<A0>(static_cast<bd::as_integer_t<A0>>(a0));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0 a0) const BOOST_NOEXCEPT
    {
      return std::trunc(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &
                                    ,  A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

} } }


#endif
