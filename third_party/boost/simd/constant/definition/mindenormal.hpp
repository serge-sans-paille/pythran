//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MINDENORMAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MINDENORMAL_HPP_INCLUDED

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
    struct mindenormal_ : boost::dispatch::constant_value_<mindenormal_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mindenormal_,boost::dispatch::constant_value_<mindenormal_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x1UL, 0x1ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mindenormal_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mindenormal_,mindenormal);
  }

  template<typename T> BOOST_FORCEINLINE auto Mindenormal()
  BOOST_NOEXCEPT_DECLTYPE(detail::mindenormal( boost::dispatch::as_<T>{}))
  {
    return detail::mindenormal( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mindenormal(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mindenormal<T>())
  {
    return Mindenormal<T>();
  }
} }

#endif
