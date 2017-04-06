//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_HUNDRED_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_HUNDRED_HPP_INCLUDED

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
    struct hundred_ : boost::dispatch::constant_value_<hundred_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,hundred_,boost::dispatch::constant_value_<hundred_>);
      BOOST_SIMD_REGISTER_CONSTANT(100, 0x42c80000U, 0x4059000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, hundred_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::hundred_,hundred);
  }

  template<typename T> BOOST_FORCEINLINE auto Hundred()
  BOOST_NOEXCEPT_DECLTYPE(detail::hundred( boost::dispatch::as_<T>{}))
  {
    return detail::hundred( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Hundred(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Hundred<T>())
  {
    return Hundred<T>();
  }
} }

#endif
