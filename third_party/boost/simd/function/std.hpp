//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_STD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_STD_HPP_INCLUDED

#include <boost/simd/detail/decorator.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-decorator

    provides an easy way to use the original  stdlibc++ function that is mimicked by one of our functors.


    @par Header <boost/simd/function/std.hpp>

    @par Semantic

    For a function object @c func,

    @code
    auto std_func = std_(func);
    @endcode

    is equivalent to:

    @code
    T r = std::func(< func parameters >);
    @endcode

    @par Notes

    - for simd vector parameter a map of the standard function is done automagically
      for each vector element but of course there is no vectorization gain.

    - std_ is only a convenience feature for people which
      sometimes have to stick to the standard or
      test the standard behaviour against **Boost.SIMD**.

  **/
  const detail::decorator<std_tag> std_ = {};
} }
#endif

namespace boost { namespace simd
{
  struct std_tag : decorator_<std_tag>
  {
    using parent = decorator_<std_tag>;
  };

  const detail::decorator<std_tag> std_ = {};
} }

#endif
