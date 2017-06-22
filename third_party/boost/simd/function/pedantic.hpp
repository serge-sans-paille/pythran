//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_PEDANTIC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_PEDANTIC_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/detail/dispatch.hpp>
#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

    calls a version of the functor
      that can do some aggressive optimization at the cost of certain
      properties or corner cases of the original functor.

      These losses are of the `pedantic_math` kind.


    @par Header <boost/simd/function/pedantic.hpp>

    @par Semantic

    @code
    T r = pedantic_(func)(< func parameters >);
    @endcode

  **/
  template<typename T> auto pedantic_(T const& x) {}
} }
#endif

namespace boost { namespace simd
{
  struct pedantic_tag : decorator_<pedantic_tag>
  {
    using parent = decorator_<pedantic_tag>;
  };

  const detail::decorator<pedantic_tag> pedantic_ = {};
} }

#endif
