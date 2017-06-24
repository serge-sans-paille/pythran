//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_FIND_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_FIND_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns an iterator to the first element in the range [first,last)
    for which the element equals val.
    If no such element is found, the function returns last.

    @param first  Beginning of the range of elements to find
    @param last   End of the range of elements to find
    @param val    Value to search for in the range.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c val must be a scalar value convertible to the pointee type of first.

    @par Example:

       @snippet find.cpp find

    @par possible output:

       @snippet find.txt find

    @return An iterator to the first element in the range that compares equal to val.
            If no elements match, the function returns last.
  **/
  template<typename T, typename U>
  T const* find(T const* first, T const* last, U const & val)
  {
    auto pr = segmented_aligned_range(first,last);

    auto r = std::find(pr.head.begin(), pr.head.end(), val);
    if (r != pr.head.end()) return r;

    pack<T> v(val);
    auto rv = std::find_if( pr.body.begin(), pr.body.end()
                          , [&v](const pack<T>& x) { return any(v == x); }
                          );

    if (rv != pr.body.end())
    {
      pack<T> vv = *rv;
      auto z = std::find(vv.begin(), vv.end(), val);

      // If there is somethign ina vector, compute the scalar iterator to it
      return  pr.head.end()                                           //   base
            + std::distance(pr.body.begin(), rv)*pack<T>::static_size // + jump to vector
            + std::distance(vv.begin(), z);                           // + jump to element
    }

    return std::find(pr.tail.begin(), pr.tail.end(), val);
  }
} }

#endif
