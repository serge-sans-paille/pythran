//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_INSERT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_INSERT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, insert_, boost::dispatch::abstract_<insert_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, insert_)
  }
  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::insert_,insert);
  }

  template <class P, class I,  class V> BOOST_FORCEINLINE
  void insert(P & a,  I const & i,  V const & v) BOOST_NOEXCEPT
  {
    detail::insert(a, i, v);
  }

  template < size_t N, class P,  class V> BOOST_FORCEINLINE
  void insert(P & a,  V const & v) BOOST_NOEXCEPT
  {
    detail::insert(a, nsm::size_t<N>(), v);
  }

} }

#endif
