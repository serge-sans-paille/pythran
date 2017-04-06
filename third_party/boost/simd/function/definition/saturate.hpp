//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_SATURATE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, saturate_, boost::dispatch::elementwise_<saturate_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, saturate_)
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::saturate_,saturate);
  }

  template<typename T, typename A> BOOST_FORCEINLINE A saturate(const A& a) BOOST_NOEXCEPT
  {
    return functional::saturate(a, as_<T>());
  }
} }

#endif
