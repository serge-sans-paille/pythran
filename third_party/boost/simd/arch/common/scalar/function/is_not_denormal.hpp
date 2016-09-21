//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_NOT_DENORMAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_NOT_DENORMAL_HPP_INCLUDED

#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/constant/true.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/is_not_less.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( is_not_denormal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() (const A0& ) const BOOST_NOEXCEPT
    {
      return true;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_not_denormal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    using result = bs::as_logical_t<A0>;
    BOOST_FORCEINLINE result operator() (const A0& ) const BOOST_NOEXCEPT
    {
      return True<result>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_not_denormal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE  bs::as_logical_t<A0> operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return (is_eqz(a0) ||  is_not_less(bs::abs(a0), Smallestposval<A0>()));
    }
  };

} } }


#endif
