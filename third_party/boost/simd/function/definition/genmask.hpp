//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_GENMASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, genmask_, boost::dispatch::elementwise_<genmask_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, genmask_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::genmask_,genmask);
  }

  template<typename A>  BOOST_FORCEINLINE
  auto genmask(const A& a) BOOST_NOEXCEPT_DECLTYPE_BODY(detail::genmask(a))

  template<typename T, typename A> BOOST_FORCEINLINE T genmask(const A& a) BOOST_NOEXCEPT
  {
    return detail::genmask(a, as_<T>());
  }
} }

#endif
