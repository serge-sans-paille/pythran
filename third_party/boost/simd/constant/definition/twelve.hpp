//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TWELVE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TWELVE_HPP_INCLUDED

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
    struct twelve_ : boost::dispatch::constant_value_<twelve_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,twelve_,boost::dispatch::constant_value_<twelve_>);
      BOOST_SIMD_REGISTER_CONSTANT(12,0x41400000UL, 0x4028000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, twelve_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::twelve_,twelve);
  }

  template<typename T> BOOST_FORCEINLINE auto Twelve()
  BOOST_NOEXCEPT_DECLTYPE(detail::twelve( boost::dispatch::as_<T>{}))
  {
    return detail::twelve( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Twelve(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Twelve<T>())
  {
    return Twelve<T>();
  }
} }

#endif
