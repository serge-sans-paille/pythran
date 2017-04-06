//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_EXPX2C2_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_EXPX2C2_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the constant expx2c2.

    @return The Expx2c2 constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct expx2c2_ : boost::dispatch::constant_value_<expx2c2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,expx2c2_,boost::dispatch::constant_value_<expx2c2_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3d000000UL, 0x3f80000000000000ull);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, expx2c2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::expx2c2_,expx2c2);
  }

  template<typename T> BOOST_FORCEINLINE auto Expx2c2()
  BOOST_NOEXCEPT_DECLTYPE(detail::expx2c2( boost::dispatch::as_<T>{}))
  {
    return detail::expx2c2( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
