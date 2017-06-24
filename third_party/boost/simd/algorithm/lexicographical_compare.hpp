//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/compare_less.hpp>
#include <boost/simd/function/compare_equal.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns true if the range [first1, last1) is lexicographically less than the second range
    [first2, last2), and false otherwise

    @param first1, last1  -   the first range of elements to compare
    @param first2, last2  -   the second range of elements to compare

    @par Requirement

      - @c first1 , @c last1  @c first2 , @c last2 must be pointer to Vectorizable type.


    @par Example:

      @snippet lexicographical_comparerange.cpp lexicographical_comparerange

    @par Possible output:

      @snippet lexicographical_comparerange.txt lexicographical_comparerange

  **/
  template<typename T>
  bool lexicographical_compare(T const* first1, T const* last1, const T* first2, const T* last2)
  {
    using vT = pack<T>;
    using  itype_t = typename std::iterator_traits<const T*>::difference_type;
    itype_t d1 =  std::distance(first1, last1);
    itype_t d2 =  std::distance(first2, last2);
    bool shorter =  d1 < d2;
    auto last1b = shorter ?  last1 : first1+d2;

    auto pr = segmented_aligned_range(first1,last1b);

    // prologue
    for( auto const & e : pr.head ){
      if (e < *first2) return true;
      if (*first2 < e) return false;
      ++first2;
    }


    // main SIMD part - checks if we can store efficiently or not
    if(boost::simd::detail::is_aligned(first2, vT::alignment))
    {
      for( auto const& e : pr.body )
      {
        auto e2 = aligned_load<vT>(first2);
        if(compare_less(e, e2)) return true;
        if(compare_less(e2, e)) return false;
        first2 += vT::static_size;
      }
    }
    else
    {
      for( auto const& e : pr.body )
      {
        auto e2 = load<vT>(first2);
        if(compare_less(e, e2)) return true;
        if(compare_less(e2, e)) return false;
        first2 += vT::static_size;
      }
    }

    // epilogue
    for( auto const & e : pr.tail ){
      if (e < *first2) return true;
      if (*first2 < e) return false;
      ++first2;
    }
    return shorter;
  }

  /*!
    @ingroup group-algo

     Returns true if the range [first1, last1) is lexicographically less than the second range
    [first2, first2 + (last1 - first1)), and false otherwise using comp as elementwise comparison


    @param first1, last1  -   the first range of the elements to compare
    @param first2, last2  -   the second range of the elements to compare
    @param comp           -   binary predicate operation function object that will be applied.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

      - @c comp must be a polymorphic binary function object, i.e callable on generic types.

      - Two ranges are compared element by element.
      - The first mismatching element defines which range is lexicographically less or greater than the other.
      - If one range is a prefix of another, the shorter range is lexicographically less than the other.
      - If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
      - An empty range is lexicographically less than any non-empty range.
      - Two empty ranges are lexicographically equal.

      @par Example:
         @snippet lexicographical_comparerange.cpp lexicographical_comparerange
      @par Possible output:
         @snippet lexicographical_comparerange.txt lexicographical_comparerange

  **/
  template<typename T, typename Pred>
  bool lexicographical_compare(T const* first1, T const* last1, T const* first2, T const* last2, Pred comp)
  {
    using vT = pack<T>;
    using  itype_t = typename std::iterator_traits<const T*>::difference_type;
    itype_t d1 =  std::distance(first1, last1);
    itype_t d2 =  std::distance(first2, last2);
    bool shorter =  d1 < d2;
    auto last1b = shorter ?  last1 : first1+d2;

    auto pr = segmented_aligned_range(first1,last1b);
    // prologue
    for( auto const & e : pr.head ){
      if (comp(e, *first2)) return true;
      if (comp(*first2, e)) return false;
      ++first2;
    }

    // main SIMD part - checks if we can store efficiently or not
    if(boost::simd::detail::is_aligned(first2, vT::alignment))
    {
      for( auto const& e : pr.body )
      {
        auto e2 = aligned_load<vT>(first2);
        if(comp(e, e2)) return true;
        if(comp(e2, e)) return false;
        first2 += vT::static_size;
      }
    }
    else
    {
      for( auto const& e : pr.body )
      {
        auto e2 = load<vT>(first2);
        if(comp(e, e2)) return true;
        if(comp(e2, e)) return false;
        first2 += vT::static_size;
      }
    }

    // epilogue
    for( auto const & e : pr.tail ){
      if (comp(e, *first2)) return true;
      if (comp(*first2, e)) return false;
      ++first2;
    }
    return shorter;
  }

} }

#endif
