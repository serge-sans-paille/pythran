//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SEVEN_HPP_INCLUDED

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
    struct seven_ : boost::dispatch::constant_value_<seven_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,seven_,boost::dispatch::constant_value_<seven_>);
      BOOST_SIMD_REGISTER_CONSTANT( 7, 0x40e00000UL, 0x401c000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, seven_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::seven_,seven);
  }

  template<typename T> BOOST_FORCEINLINE auto Seven()
  BOOST_NOEXCEPT_DECLTYPE(detail::seven( boost::dispatch::as_<T>{}))
  {
    return detail::seven( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Seven(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Seven<T>())
  {
    return Seven<T>();
  }
} }

#endif
