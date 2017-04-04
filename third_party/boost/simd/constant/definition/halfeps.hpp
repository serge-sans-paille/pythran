//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_HALFEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_HALFEPS_HPP_INCLUDED

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
    struct halfeps_ : boost::dispatch::constant_value_<halfeps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,halfeps_,boost::dispatch::constant_value_<halfeps_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x33800000, 0x3CA0000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, halfeps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::halfeps_,halfeps);
  }

  template<typename T> BOOST_FORCEINLINE auto Halfeps()
  BOOST_NOEXCEPT_DECLTYPE(detail::halfeps( boost::dispatch::as_<T>{}))
  {
    return detail::halfeps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Halfeps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Halfeps<T>())
  {
    return Halfeps<T>();
  }
} }

#endif
