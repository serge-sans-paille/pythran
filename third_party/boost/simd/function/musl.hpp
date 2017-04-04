//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MUSL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MUSL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>
#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

    calls a version of the functor for which the algorithm is inspired by the musl
    library code.


    @par Header <boost/simd/function/musl.hpp>

    @par Semantic

    @code
    T r = musl_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto musl_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct musl_tag : decorator_<musl_tag>
  {
    using parent = decorator_<musl_tag>;
  };

  const detail::decorator<musl_tag> musl_ = {};
} }

#endif
