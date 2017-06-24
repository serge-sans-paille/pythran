//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_FILL_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_FILL_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Fill the COntiguousRange [first,last) with a given value

    @param first  Beginning of the range of elements to test
    @param last   End of the range of elements to fill
    @param value  value to fill the range with

    @par Requirement

      - @c first and @c last must be pointers to Vectorizable type.

    @par Example;:

      @snippet fill.cpp fill

    @par Possible output:

      @snippet fill.txt fill

  **/
  template<typename T, typename U> void fill(T * first, T * last, U value)
  {
    auto pr = segmented_aligned_range(first,last);
    std::fill(pr.head.begin(), pr.head.end(), value);
    std::fill(pr.body.begin(), pr.body.end(), pack<T>(value));
    std::fill(pr.tail.begin(), pr.tail.end(), value);
  }
} }

#endif
