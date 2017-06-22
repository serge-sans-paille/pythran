//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ABS_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/mzero.hpp>
#include <boost/simd/function/bitwise_notand.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>
#include <cstdlib>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a) const BOOST_NOEXCEPT
    {
      using utype = dispatch::as_unsigned_t<T>;

      utype mask = a >> (sizeof(T)*8 - 1);
      return (a + mask) ^ mask;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a) const BOOST_NOEXCEPT
    {
      return bitwise_notand(Mzero<T>(),a);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::unsigned_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::bool_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( std_tag const&, T a) const BOOST_NOEXCEPT
    {
      return std::fabs(a);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_<bd::unsigned_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( std_tag const&, T a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( std_tag const&,T a) const BOOST_NOEXCEPT
    {
      return std::abs(a);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_<bd::signed_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a0) const BOOST_NOEXCEPT
    {
      return (a0==Valmin<T>())?Valmax<T>():bs::abs(a0);
    }
  };
} } }

#include <boost/simd/arch/common/scalar/function/abs_s.hpp>

#endif
