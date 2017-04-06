//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_SLIDE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, slide_, boost::dispatch::abstract_<slide_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, slide_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::slide_,slide);
  }
} }

#include <boost/simd/function/detail/slide.hpp>

namespace boost { namespace simd
{
  template<int N, typename T> BOOST_FORCEINLINE T slide(T const& a0, T const& a1)
  {
    return detail::slider<T,N,cardinal_of<T>::value,(N>=0)>::call(a0,a1);
  }

  template<int N, typename T> BOOST_FORCEINLINE T slide(T const& a0)
{
    return detail::slider<T,N,cardinal_of<T>::value,(N>=0)>::call(a0);
  }
} }

#endif
