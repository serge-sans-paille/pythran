//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, shuffle_, boost::dispatch::abstract_<shuffle_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, shuffle_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::shuffle_,shuffle_impl);
  }

  // Integer version
  template<int... Ps, typename T> BOOST_FORCEINLINE T shuffle(T const& a) BOOST_NOEXCEPT
  {
    return detail::shuffle_impl(detail::pattern_<Ps...>(), a);
  }
  template<int... Ps, typename T> BOOST_FORCEINLINE T shuffle(T const& a,T const& b) BOOST_NOEXCEPT
  {
    return detail::shuffle_impl(detail::pattern_<Ps...>(), a, b);
  }

  // (Meta)function version
  template<typename Perm, typename T> BOOST_FORCEINLINE T shuffle(T const& a) BOOST_NOEXCEPT
  {
    using p_t = typename detail::meta_pattern<Perm,T>::type;
    return detail::shuffle_impl(p_t(), a);
  }

  template<typename Perm, typename T> BOOST_FORCEINLINE T shuffle(T const& a,T const& b) BOOST_NOEXCEPT
  {
    using p_t = typename detail::meta_pattern<Perm,T>::type;
    return detail::shuffle_impl(p_t(), a, b);
  }
} }

#endif
