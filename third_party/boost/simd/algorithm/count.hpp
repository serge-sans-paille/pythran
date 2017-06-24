//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_COUNT_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_COUNT_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns the number of elements in the ContiguousRange [first,last) that compare equal to val.

    @param first  Beginning of the range of elements to count
    @param last   End of the range of elements to count
    @param val    Value to search for in the range.

    @par Requirement

      - @c first, @c last and @c out must be pointers to Vectorizable type.
      - @c val must be a scalar value convertible to the pointee type of first.

    @par Example:

      @snippet count.cpp count

    @par Possible output:

      @snippet count.txt count

  **/
  template<typename T, typename U>
  typename std::iterator_traits<const T*>::difference_type
  count(T const* first, T const* last, U const & val)
  {
    pack<T> pval(val);
    auto pr = segmented_aligned_range(first,last);

    auto c = std::count(pr.head.begin(), pr.head.end(), val);
    for(pack<T> x : pr.body)   c += nbtrue(x == pval);
    c += std::count(pr.tail.begin(), pr.tail.end(), val);

    return c;
  }
} }

#endif
