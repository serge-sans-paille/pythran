//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_ANY_OF_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_ANY_OF_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/detail/identity.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/pack.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns @ true if @c pred avaluates to @c true for any of the elements in the
    ContiguousRange [first,last), and ^c false otherwise (in particular when the range is empty).

    @param first  Beginning of the range of elements to test
    @param last   End of the range of elements to test
    @param pred   Predicate function object that will be applied.

    @par Requirement

      - @c first and @c last must be pointers to Vectorizable type.
      - @c pred must be a polymorphic unary function object, i.e callable on generic types.

    @par Example:

      @snippet any_of.cpp any_of

    @par Possible output:

      @snippet any_of.txt any_of
  **/
  template<typename T, typename Pred> bool any_of(T const* first, T const* last, Pred const& pred)
  {
    auto pr = segmented_aligned_range(first,last);

    if(std::any_of(pr.head.begin(), pr.head.end(), pred))
      return true;

    if( std::any_of ( pr.body.begin(), pr.body.end()
                    , [&pred](pack<T> const& x){ return any(pred(x)); }
                    )
      )
      return true;

    if (std::any_of(pr.tail.begin(), pr.tail.end(), pred))
      return true;

    return false;
  }

  /*!
    @ingroup group-algo

    Returns @ true if any of the elements in the ContiguousRange [first,last) is
    not equal to zero, and @c false otherwise (in particular when the range is empty).

    @param first  Beginning of the range of elements to test
    @param last   End of the range of elements to test

    @par Requirement

      - @c first and @c last must be pointers to Vectorizable type.
  **/
  template<typename T> bool any_of(T const* first, T const* last)
  {
    return any_of(first, last, detail::identity());
  }
} }

#endif
