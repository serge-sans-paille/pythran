//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_HALF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_HALF_HPP_INCLUDED

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
    struct half_ : boost::dispatch::constant_value_<half_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,half_,boost::dispatch::constant_value_<half_>);
      BOOST_SIMD_REGISTER_CONSTANT(0,0x3F000000,0x3FE0000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, half_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::half_,half);
  }

  template<typename T> BOOST_FORCEINLINE auto Half()
  BOOST_NOEXCEPT_DECLTYPE(detail::half( boost::dispatch::as_<T>{}))
  {
    return detail::half( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Half(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Half<T>())
  {
    return Half<T>();
  }
} }

#endif
