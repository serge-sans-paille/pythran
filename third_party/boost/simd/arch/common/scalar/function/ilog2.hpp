//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOG2_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/clz.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD(ilog2_, (typename A0), bd::cpu_, bd::scalar_<bd::floating_<A0>>)
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( a0 > 0
                      , "Logarithm is not defined for zero or negative values." );
      return exponent(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD(ilog2_, (typename A0), bd::cpu_, bd::scalar_<bd::arithmetic_<A0>>)
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( a0 > 0
                      , "Logarithm is not defined for zero or negative values." );
      return A0(sizeof(A0)*8-boost::simd::clz(a0)-1);
    }
  };

#if defined(BOOST_MSVC)
  BOOST_DISPATCH_OVERLOAD(ilog2_, (typename A0), bd::cpu_, bd::scalar_<bd::integer_<A0>>)
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( a0 > 0, "Logarithm is not defined for zero or negative values." );
      return impl(a0, typename nsm::bool_<sizeof(A0) <= 4>::type());
    }

    static BOOST_FORCEINLINE A0 impl( A0  a0,  tt::true_type const &) BOOST_NOEXCEPT
    {
      unsigned long index;
      BOOST_VERIFY(::_BitScanReverse(&index, a0));
      return static_cast<A0>(index);
    }

    #if defined(_WIN64)
    static BOOST_FORCEINLINE A0 impl(A0 a0, tt::false_type const &) BOOST_NOEXCEPT
    {
      unsigned long index;
      BOOST_VERIFY(::_BitScanReverse64(&index, a0));
      return static_cast<A0>(index);
    }
    #else
    static BOOST_FORCEINLINE A0 impl(A0 a0, tt::false_type const &) BOOST_NOEXCEPT
    {
      return static_cast<A0>(sizeof(A0)*8-boost::simd::clz(a0)-1);
    }
    #endif
  };
  #endif
} } }

#endif
