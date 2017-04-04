//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_PIO_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_PIO_6_HPP_INCLUDED

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
    struct pio_6_ : boost::dispatch::constant_value_<pio_6_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio_6_,boost::dispatch::constant_value_<pio_6_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3F060A92UL, 0X3FE0C152382D7366ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio_6_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio_6_,pio_6);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio_6()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio_6( boost::dispatch::as_<T>{}))
  {
    return detail::pio_6( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Pio_6(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Pio_6<T>())
  {
    return Pio_6<T>();
  }
} }

#endif
