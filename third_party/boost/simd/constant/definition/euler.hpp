//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_EULER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_EULER_HPP_INCLUDED

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
    struct euler_ : boost::dispatch::constant_value_<euler_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,euler_,boost::dispatch::constant_value_<euler_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0X3F13C468UL, 0X3FE2788CFC6FB619ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, euler_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::euler_,euler);
  }

  template<typename T> BOOST_FORCEINLINE auto Euler()
  BOOST_NOEXCEPT_DECLTYPE(detail::euler( boost::dispatch::as_<T>{}))
  {
    return detail::euler( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Euler(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Euler<T>())
  {
    return Euler<T>();
  }
} }

#endif
