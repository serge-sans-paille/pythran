//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SQRTPIO_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SQRTPIO_2_HPP_INCLUDED

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
    struct sqrtpio_2_ : boost::dispatch::constant_value_<sqrtpio_2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,sqrtpio_2_,boost::dispatch::constant_value_<sqrtpio_2_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3F62DFC5, 0X3FEC5BF891B4EF6BLL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, sqrtpio_2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::sqrtpio_2_,sqrtpio_2);
  }

  template<typename T> BOOST_FORCEINLINE auto Sqrtpio_2()
  BOOST_NOEXCEPT_DECLTYPE(detail::sqrtpio_2( boost::dispatch::as_<T>{}))
  {
    return detail::sqrtpio_2( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Sqrtpio_2(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Sqrtpio_2<T>())
  {
    return Sqrtpio_2<T>();
  }
} }

#endif
