//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLATTED_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLATTED_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/decorator.hpp>

namespace boost { namespace simd
{
  struct splatted_tag : decorator_<splatted_tag>
  {
    using parent = decorator_<splatted_tag>;
  };

  /*!
    @ingroup group-decorator
    Decorator for selecting splatted version of reduction function.

    Reduction functions operating on SIMD pack returns a single scalar value.
    For efficiency issue, it may be interesting to retrieve this result as a
    SIMD pack containing said value in all of its element. The splatted_ decorator
    allow for such optimization.


    @par Header <boost/simd/function/splatted.hpp>

    @par Semantic:

    For any reduction function @c r and any SIMD pack @ p , the following code:

    @code
    auto v = splatted_(r)(p);
    @endcode

    is equivalent to:

    @code
    auto v = splat<decltype(p)>(r(p));
    @endcode
  **/
  const detail::decorator<splatted_tag> splatted_ = {};
} }

#endif
