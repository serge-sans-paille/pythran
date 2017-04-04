//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_LOAD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_LOAD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, load_, boost::dispatch::abstract_<load_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, load_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::load_,load_impl);
  }

  template<typename Type, typename Source, typename... Opts>
  BOOST_FORCEINLINE Type load(Source const& p, Opts&&... o)
  {
    return detail::load_impl( p, std::forward<Opts>(o)..., boost::simd::as_<Type>() );
  }
} }

#endif
