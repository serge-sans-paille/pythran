//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SQRT_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SQRT_2_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct sqrt_2_ : boost::dispatch::constant_value_<sqrt_2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,sqrt_2_,boost::dispatch::constant_value_<sqrt_2_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x3FB504F3UL, 0x3ff6A09E667F3BCCULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, sqrt_2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::sqrt_2_,sqrt_2);
  }

  template<typename T> BOOST_FORCEINLINE auto Sqrt_2()
  BOOST_NOEXCEPT_DECLTYPE(detail::sqrt_2( boost::dispatch::as_<T>{}))
  {
    return detail::sqrt_2( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Sqrt_2(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Sqrt_2<T>())
  {
    return Sqrt_2<T>();
  }
} }

#endif
