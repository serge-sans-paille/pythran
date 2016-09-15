//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FAST_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>
#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
  @ingroup group-decorator

    calls a version of the functor
      that can do some agressive optimization at the cost of certain
      properties or corner cases of the original functor.

      These losses are of the `fast_math` kind.

    @par Semantic

    @code
    T r = fast_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto fast_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct fast_tag : decorator_<fast_tag>
  {
    using parent = decorator_<fast_tag>;
  };

  const detail::decorator<fast_tag> fast_ = {};
} }

#endif
