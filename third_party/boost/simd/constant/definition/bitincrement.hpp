//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_BITINCREMENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_BITINCREMENT_HPP_INCLUDED

#include <boost/simd/config.hpp>
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
    struct bitincrement_ : boost::dispatch::constant_value_<bitincrement_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,bitincrement_,boost::dispatch::constant_value_<bitincrement_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x1UL, 0x1ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, bitincrement_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::bitincrement_,bitincrement);
  }

  template<typename T> BOOST_FORCEINLINE auto Bitincrement()
  BOOST_NOEXCEPT_DECLTYPE(detail::bitincrement( boost::dispatch::as_<T>{}))
  {
    return detail::bitincrement( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Bitincrement(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Bitincrement<T>())
  {
    return Bitincrement<T>();
  }
} }

#endif
