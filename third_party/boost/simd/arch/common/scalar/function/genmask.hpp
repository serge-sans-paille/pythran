//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_GENMASK_HPP_INCLUDED

#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // genmask from logical
  BOOST_DISPATCH_OVERLOAD ( genmask_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bs::logical_<A0> >
                          )
  {
    using result_t = as_arithmetic_t<A0>;

    BOOST_FORCEINLINE result_t operator()( A0 const& a0 ) const BOOST_NOEXCEPT
    {
      using itype = dispatch::as_integer_t<result_t>;
      return bitwise_cast<result_t>(unary_minus(itype(a0)));
    }
  };

  // -----------------------------------------------------------------------------------------------
  // genmask for bool
  BOOST_DISPATCH_OVERLOAD ( genmask_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( A0 const& a0 ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  // -----------------------------------------------------------------------------------------------
  // genmask from other value
  BOOST_DISPATCH_OVERLOAD ( genmask_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( A0 const& a0 ) const BOOST_NOEXCEPT
    {
      using itype = dispatch::as_integer_t<A0>;
      return bitwise_cast<A0>(unary_minus(itype(a0 != 0)));
    }
  };

} } }

#endif
