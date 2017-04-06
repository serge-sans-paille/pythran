//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TANPIO_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TANPIO_8_HPP_INCLUDED

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
    struct tanpio_8_ : boost::dispatch::constant_value_<tanpio_8_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,tanpio_8_,boost::dispatch::constant_value_<tanpio_8_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3ED413CDUL, 0X3FDA827999FCEF31ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, tanpio_8_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::tanpio_8_,tanpio_8);
  }

  template<typename T> BOOST_FORCEINLINE auto Tanpio_8()
  BOOST_NOEXCEPT_DECLTYPE(detail::tanpio_8( boost::dispatch::as_<T>{}))
  {
    return detail::tanpio_8( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Tanpio_8(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Tanpio_8<T>())
  {
    return Tanpio_8<T>();
  }
} }

#endif
