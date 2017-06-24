//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_EQUAL_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/simd/function/compare_equal.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/pack.hpp>
#include <type_traits>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns true if the range [first, last) is equal
    to the range [first2, first2 + (last - first)), and false otherwise

    @param first, last    -   the first range of the elements to compare
    @param first2         -   the beginning of the second range of the elements to compare

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

    @par Example:

      @snippet equalrange.cpp equalrange

    @par Possible output:

      @snippet equalrange.txt equalrange

  **/
  template<typename T>
  bool equal(T const* first, T const* last, const T* first2)
  {
    auto pr = segmented_aligned_range(first,last);

    for(T e : pr.head) if (!(e == *first2++)) return false;

    // main SIMD part - checks if we can load efficiently or not
    if(boost::simd::detail::is_aligned(first2, pack<T>::alignment))
    {
      for(pack<T> e : pr.body )
      {
        if(!compare_equal( pack<T>(first2), e)) return false;
        first2 += pack<T>::static_size;
      }
    }
    else
    {
      for(pack<T> e : pr.body )
      {
        if(!compare_equal(load<pack<T>>(first2), e)) return false;
        first2 += pack<T>::static_size;
      }
    }

    for(T e : pr.tail ) if(!(e == *first2++)) return false;

    return true;
  }

  /*!
    @ingroup group-algo

    Returns true if all the pairs in the range [first1, last1) and the
    range [first2, first2 + (last1 - first1)), satisfy f and false otherwise

    @param first1, last1  -   the first range of the elements to compare
    @param first2         -   the beginning of the second range of the elements to compare
    @param f       binary predicate operation function object that will be applied.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c f must be a polymorphic binary function object, i.e callable on generic types.
      -  boost::simd::pack<T1> and boost::simd::pack<T2> must have the same cardinal.

    @par Example:

      @snippet equalrange.cpp equalrange

    @par Possible output:

      @snippet equalrange.txt equalrange

  **/
  template<typename T, typename Pred>
  bool equal(T const* first1, T const* last1, T const* first2, Pred const& f)
  {
    auto pr = segmented_aligned_range(first1,last1);

    for(T e : pr.head ) if (!f(e, *first2++)) return false;

    if(  boost::simd::detail::is_aligned(first2 , pack<T>::alignment))
    {
      for(pack<T> e : pr.body )
      {
        if(!all(f(e, pack<T>(first2)))) return false;
        first2  += pack<T>::static_size;
      }
    }
    else
    {
      for(pack<T> e : pr.body )
      {
        if(!all(f(e, load<pack<T>>(first2)))) return false;
        first2  += pack<T>::static_size;
      }
    }

    for(T e : pr.tail )  if (!f(e, *first2++)) return false;

    return true;
  }
} }

#endif
