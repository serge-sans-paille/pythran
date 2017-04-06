//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TRUE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TRUE_HPP_INCLUDED

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
    BOOST_DISPATCH_MAKE_TAG(ext, true_, boost::dispatch::constant_value_<true_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, true_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::true_,true_);
  }

  template<typename T>
  BOOST_FORCEINLINE     auto True()
                    ->  decltype(detail::true_( boost::dispatch::as_<T>{}))
  {
    return detail::true_( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto True(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(True<T>())
  {
    return True<T>();
  }
} }

#endif
