//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACCURATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACCURATE_HPP_INCLUDED

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

      These losses are of the `accurate_math` kind.

    @par Semantic

    @code
    T r = accurate_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto accurate_(T const& x) {}

} }
#endif

namespace boost { namespace simd
{
  struct accurate_tag : decorator_<accurate_tag>
  {
    using parent = decorator_<accurate_tag>;
  };

  const detail::decorator<accurate_tag> accurate_ = {};
} }

#endif
