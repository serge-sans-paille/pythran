//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INVLOG10_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INVLOG10_2_HPP_INCLUDED

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
    struct invlog10_2_ : boost::dispatch::constant_value_<invlog10_2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,invlog10_2_,boost::dispatch::constant_value_<invlog10_2_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x40549a78UL, 0x400a934f0979a371ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, invlog10_2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::invlog10_2_,invlog10_2);
  }

  template<typename T> BOOST_FORCEINLINE auto Invlog10_2()
  BOOST_NOEXCEPT_DECLTYPE(detail::invlog10_2( boost::dispatch::as_<T>{}))
  {
    return detail::invlog10_2( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Invlog10_2(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Invlog10_2<T>())
  {
    return Invlog10_2<T>();
  }
} }

#endif
