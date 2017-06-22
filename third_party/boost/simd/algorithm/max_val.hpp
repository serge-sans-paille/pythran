//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_MAX_VAL_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_MAX_VAL_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/maximum.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/detail/is_aligned.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns the value of the element with the smallest value in the range [first,last),
    The largest possible value for the order if the range is empty.

    @param first  Beginning of the range of elements to max_val
    @param last   End of the range of elements to max_val
    @param comp   comparison function object that will be applied.

    @par Requirement

      - @c first and @c last must be pointer to Vectorizable type.

      - @c comp must be a polymorphic unary function object, i.e callable on generic types.
      - if @c comp is not present the function test is done with operator <

    @par Example

    The following code uses simd::max_val to find the greatest and smallest element
    @c std::vector.
    @snippet max_val.cpp max_val
    @snippet max_val.txt max_val

    @return the maximum value of the range elements.
  **/
  template<typename T, typename Comp>
  T max_val(T const* first, T const* last, Comp comp)
  {
    if (first == last) return comp(T(0), T(1)) ? Inf<T>() : Minf<T>();
    auto pr = segmented_aligned_range(first,last);

    T m = *first;
    for( T e : pr.head ) { if (comp(m, e))  m = e; }

    // main SIMD part
    pack<T> mm(m);
    for(pack<T> e : pr.body ) mm =  if_else(comp(m, e), e, m);

    m =  mm[0];
    for(T v : mm) if(comp(m, v)) m = v;

    for( T e : pr.tail ) { if(comp(m, e))  m = e; }

    return m;
  }

  /*!
    @ingroup group-algo

    Returns the value of the element with the smallest value in the range [first,last),
    The largest possible value for the order if the range is empty.

    @param first  Beginning of the range of elements to max_val
    @param last   End of the range of elements to max_val

    @par Requirement

      - @c first and @c last must be pointer to Vectorizable type.

    @par Example

    The following code uses simd::max_val to find the greatest and smallest element
    @c std::vector.
    @snippet max_val.cpp max_val
    @snippet max_val.txt max_val

    @return the maximum value of the range elements.
  **/
  template<typename T> T max_val(T const* first, T const* last)
  {
    if (first == last) return Minf<T>();
    auto pr = segmented_aligned_range(first,last);

    T m = *first;
    for( T e : pr.head ) m = max(e, m);

    pack<T> mm(m);
    for(pack<T> e : pr.body ) mm = max(e, mm);

    m =  maximum(mm);
    for(T e : pr.tail ) m = max(e, m);

    return m;
  }
} }

#endif
