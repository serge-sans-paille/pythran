//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INVEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INVEPS_HPP_INCLUDED

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
    struct inveps_ : boost::dispatch::constant_value_<inveps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,inveps_,boost::dispatch::constant_value_<inveps_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x4b000000UL, 0x4330000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,inveps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::inveps_,inveps);
  }

  template<typename T> BOOST_FORCEINLINE auto Inveps()
  BOOST_NOEXCEPT_DECLTYPE(detail::inveps( boost::dispatch::as_<T>{}))
  {
    return detail::inveps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Inveps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Inveps<T>())
  {
    return Inveps<T>();
  }
} }

#endif
