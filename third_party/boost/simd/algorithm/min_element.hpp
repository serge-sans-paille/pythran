//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_MIN_ELEMENT_HPP_INCLUDED

#include <boost/simd/algorithm/find.hpp>
#include <boost/simd/algorithm/min_val.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns an iterator pointing to the element with the smallest value in the range [first,last).

    @param first  Beginning of the range of elements to min_element
    @param last   End of the range of elements to min_element
    @param comp   comparison function object that will be applied.

    @par Requirement

      - @c first and @c last must be pointer to Vectorizable type.

      - @c comp must be a polymorphic unary function object, i.e callable on generic types.
      - if @c comp is not present the function test is done with operator <

    @par Example:

      @snippet min_element.cpp min_element

    @par Possible output:

      @snippet min_element.txt min_element

  **/
  template<typename T, typename Comp>
  T const * min_element(T const* first, T const* last, Comp comp)
  {
    if (first == last) return last;
    return find(first, last, min_val(first,last,comp));
  }

  template<typename T> T const * min_element(T const* first, T const* last)
  {
    if (first == last) return last;
    return find(first, last, min_val(first,last));
  }
} }

#endif
