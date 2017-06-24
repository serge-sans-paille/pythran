//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_NONE_OF_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_NONE_OF_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/detail/identity.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns true if f returns false for all the elements in the range [first,last)
    or if the range is empty, and false otherwise.

    @param first  Beginning of the range of elements
    @param last   End of the range of elements
    @param f   predicate function object that will be applied.

    @par Requirement

      - @c first and @c last must be pointer to Vectorizable type.

      - @c f must be a polymorphic unary function object, i.e cnoneable on generic types.
      - if @c f is not present the function test if all elements are zero.

    @par Example:

      @snippet none_of.cpp none_of

    @par Possible output:

      @snippet none_of.txt none_of
  **/
  template<typename T, typename Pred>
  bool none_of(T const* first, T const* last, Pred f)
  {
    auto pr = segmented_aligned_range(first,last);

    if(std::any_of(pr.head.begin(), pr.head.end(), f))
      return false;

    if(std::any_of(pr.body.begin(), pr.body.end(), [&f](const pack<T>&  x){ return any(f(x)); }))
      return false;

    if(std::any_of(pr.tail.begin(), pr.tail.end(), f))
      return false;

    return true;
  }

  template<typename T> BOOST_FORCEINLINE bool none_of(T const* first, T const* last)
  {
    return none_of(first, last, detail::identity());
  }
} }

#endif
