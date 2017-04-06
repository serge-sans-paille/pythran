//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_PLAIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_PLAIN_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>
#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

    calls the plain version of the functor
    This decorator is used internally as a tag to choose the boost simd
    kernel among other


    @par Header <boost/simd/function/plain.hpp>

    @par Semantic

    @code
    T r = plain_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto plain_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct plain_tag : decorator_<plain_tag>
  {
    using parent = decorator_<plain_tag>;
  };

  const detail::decorator<plain_tag> plain_ = {};
} }

#endif
