//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, aligned_load_, boost::dispatch::abstract_<aligned_load_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, aligned_load_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::aligned_load_,aligned_load);
  }

  template<typename T, typename Pointer, typename... Opts>
  BOOST_FORCEINLINE T aligned_load(Pointer const& p, Opts&&... o)
  {
    return detail::aligned_load( p, std::forward<Opts>(o)..., boost::simd::as_<T>() );
  }

  template<typename T, std::ptrdiff_t Misalignment, typename Pointer, typename... Opts>
  BOOST_FORCEINLINE T aligned_load(Pointer const& p, Opts&&... o)
  {
    return detail::aligned_load ( p, std::forward<Opts>(o)...
                                , tt::integral_constant<std::ptrdiff_t,Misalignment>()
                                , boost::simd::as_<T>()
                                );
  }
} }

#endif
