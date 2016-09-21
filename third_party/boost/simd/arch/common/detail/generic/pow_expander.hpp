//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_POW_EXPANDER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_POW_EXPANDER_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/sqr.hpp>
namespace boost { namespace simd { namespace ext
{

  template<std::uintmax_t Exp, std::uintmax_t Odd = Exp%2>
  struct pow_expander;

  template<std::uintmax_t Exp>
  struct pow_expander<Exp, 0ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call( A0 const& a0) BOOST_NOEXCEPT
    {
      return pow_expander<Exp/2>::call(sqr(a0));
    }
  };

  template<std::uintmax_t Exp>
  struct pow_expander<Exp, 1ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call( A0 const& a0) BOOST_NOEXCEPT
    {
      return a0*pow_expander<Exp/2>::call(sqr(a0));
    }
  };

  template<>
  struct pow_expander<0ULL, 0ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call( A0 const&) BOOST_NOEXCEPT
    {
      return One<A0>();
    }
  };

  template<>
  struct pow_expander<0ULL, 1ULL>
  {
    template<class A0>
    static BOOST_FORCEINLINE A0 call( A0 const&) BOOST_NOEXCEPT
    {
      return One<A0>();
    }
  };
} } }

#endif
