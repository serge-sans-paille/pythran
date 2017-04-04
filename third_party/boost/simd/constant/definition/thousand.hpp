//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_THOUSAND_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_THOUSAND_HPP_INCLUDED

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
    struct thousand_ : boost::dispatch::constant_value_<thousand_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,thousand_,boost::dispatch::constant_value_<thousand_>);
      BOOST_SIMD_REGISTER_CONSTANT(1000, 0x447a0000UL, 0x408f400000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, thousand_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::thousand_,thousand);
  }

  template<typename T> BOOST_FORCEINLINE auto Thousand()
  BOOST_NOEXCEPT_DECLTYPE(detail::thousand( boost::dispatch::as_<T>{}))
  {
    return detail::thousand( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Thousand(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Thousand<T>())
  {
    return Thousand<T>();
  }
} }

#endif
