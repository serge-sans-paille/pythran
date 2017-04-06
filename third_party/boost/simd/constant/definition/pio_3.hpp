//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_PIO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_PIO_3_HPP_INCLUDED

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
    struct pio_3_ : boost::dispatch::constant_value_<pio_3_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio_3_,boost::dispatch::constant_value_<pio_3_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3F860A92LL, 0X3FF0C152382D7366ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio_3_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio_3_,pio_3);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio_3()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio_3( boost::dispatch::as_<T>{}))
  {
    return detail::pio_3( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Pio_3(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Pio_3<T>())
  {
    return Pio_3<T>();
  }
} }

#endif
