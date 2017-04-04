//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FALSE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FALSE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, false_, boost::dispatch::constant_value_<false_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, false_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::false_,false_);
  }

  template<typename T>
  BOOST_FORCEINLINE     auto False()
                    ->  decltype(detail::false_( boost::dispatch::as_<T>{}))
  {
    return detail::false_( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto False(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(False<T>())
  {
    return False<T>();
  }
} }

#endif
