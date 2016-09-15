//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ALL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ALL_HPP_INCLUDED

#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( all_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<logical_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( all_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator()( A0 a0) const BOOST_NOEXCEPT
    {
      return is_nez(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( all_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator()( A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }

#endif
