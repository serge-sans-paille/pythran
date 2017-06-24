//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_ALL_OF_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_ALL_OF_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/detail/identity.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns @c true if @c pred evaluates to @c true for all the elements in the
    ContiguousRange [first,last) or if the range is empty, @c and false otherwise.

    @param first  Beginning of the range of elements to test
    @param last   End of the range of elements to all_of
    @param pred   Predicate function object that will be applied.

    @par Requirement

      - @c first and @c last must be pointers to Vectorizable type.
      - @c pred must be a polymorphic unary function object, i.e callable on
        generic types.

    @par Example;:

      @snippet all_of.cpp all_of

    @par Possible output:

      @snippet all_of.txt all_of
  **/
  template<typename T, typename Pred>
  bool all_of(T const* first, T const* last, Pred const& pred)
  {
    auto pr = segmented_aligned_range(first,last);

    if(!std::all_of(pr.head.begin(), pr.head.end(), pred))
      return false;

    if(!std::all_of(pr.body.begin(), pr.body.end(), [&pred](pack<T> const& x){ return all(pred(x)); }))
      return false;

    if(!std::all_of(pr.tail.begin(), pr.tail.end(), pred))
      return false;

    return true;
  }


  /*!
    @ingroup group-algo

    Returns @c true if all the elements in the ContiguousRange [first,last) are not equal to zero
    or if the range is empty, @c and false otherwise.

    @param first  Beginning of the range of elements to test
    @param last   End of the range of elements to all_of

    @par Requirement

      - @c first and @c last must be pointers to Vectorizable type.
  **/
  template<typename T> bool all_of(T const* first, T const* last)
  {
    return all_of(first, last, detail::identity());
  }
} }

#endif
