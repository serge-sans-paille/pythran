//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_FREXP_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/config.hpp>
#include <utility>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      auto that = ifrexp(a0);
      return {that.first, tofloat(that.second)};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(const pedantic_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      auto that = pedantic_(simd::ifrexp)(a0);
      return {that.first, tofloat(that.second)};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(const raw_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      auto that = raw_(simd::ifrexp)(a0);
      return {that.first, tofloat(that.second)};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(const std_tag &, A0 a0 ) const BOOST_NOEXCEPT
    {
      auto that = std_(simd::ifrexp)(a0);
      return {that.first, tofloat(that.second)};
    }
  };
} } }

#endif
