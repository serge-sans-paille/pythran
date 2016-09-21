//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_GOLDBAR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_GOLDBAR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct goldbar_ : boost::dispatch::constant_value_<goldbar_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,goldbar_,boost::dispatch::constant_value_<goldbar_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xbf1e377aLL, 0xbfe3c6ef372fe950ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,goldbar_);
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::goldbar_,goldbar);
  }

  template<typename T> BOOST_FORCEINLINE auto Goldbar()
  BOOST_NOEXCEPT_DECLTYPE(detail::goldbar( boost::dispatch::as_<T>{}))
  {
    return detail::goldbar( boost::dispatch::as_<T>{} );
  }
} }

#endif
