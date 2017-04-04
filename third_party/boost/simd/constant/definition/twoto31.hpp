//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TWOTO31_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TWOTO31_HPP_INCLUDED

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
    struct twoto31_ : boost::dispatch::constant_value_<twoto31_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,twoto31_,boost::dispatch::constant_value_<twoto31_>);
      BOOST_SIMD_REGISTER_CONSTANT((1ULL << 31), 0x4f000000UL, 0x41e0000000000000LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, twoto31_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::twoto31_,twoto31);
  }

  template<typename T> BOOST_FORCEINLINE auto Twoto31()
  BOOST_NOEXCEPT_DECLTYPE(detail::twoto31( boost::dispatch::as_<T>{}))
  {
    return detail::twoto31( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Twoto31(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Twoto31<T>())
  {
    return Twoto31<T>();
  }
} }

#endif
