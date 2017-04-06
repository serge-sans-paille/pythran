//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_ENUMERATE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, enumerate_, boost::dispatch::unspecified_<enumerate_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, enumerate_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::enumerate_,enumerate);
  }

  template<typename T> BOOST_FORCEINLINE T enumerate() BOOST_NOEXCEPT
  {
    return detail::enumerate(as_<T>());
  }

  template<typename T, typename Seed>
  BOOST_FORCEINLINE T enumerate(const Seed& a) BOOST_NOEXCEPT
  {
    return detail::enumerate(a, as_<T>());
  }

  template<typename T, typename Seed, typename Step>
  BOOST_FORCEINLINE T enumerate(const Seed& seed, const Step& step) BOOST_NOEXCEPT
  {
    return detail::enumerate(seed, step, as_<T>());
  }
} }

#endif
