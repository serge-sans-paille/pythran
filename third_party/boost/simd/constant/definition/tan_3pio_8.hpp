//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TAN_3PIO_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TAN_3PIO_8_HPP_INCLUDED

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
    struct tan_3pio_8_ : boost::dispatch::constant_value_<tan_3pio_8_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,tan_3pio_8_,boost::dispatch::constant_value_<tan_3pio_8_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X401A827AUL, 0X4003504F333F9DE6ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, tan_3pio_8_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::tan_3pio_8_,tan_3pio_8);
  }

  template<typename T> BOOST_FORCEINLINE auto Tan_3pio_8()
  BOOST_NOEXCEPT_DECLTYPE(detail::tan_3pio_8( boost::dispatch::as_<T>{}))
  {
    return detail::tan_3pio_8( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Tan_3pio_8(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Tan_3pio_8<T>())
  {
    return Tan_3pio_8<T>();
  }
} }

#endif
