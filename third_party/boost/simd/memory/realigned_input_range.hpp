//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_REALIGNED_INPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_REALIGNED_INPUT_RANGE_HPP_INCLUDED

#include <boost/simd/memory/aligned_input_range.hpp>
#include <boost/simd/memory/details/uncheck_iterator.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd
{
/*!
    @brief Clamped adapter for SIMD read-only range

    Convert a range represented as a pair of iterators into a read-only SIMD
    aware range. This range's extrema are modified so that:

    * the beginning of the range is referencing the first aligned element of the
      original range
    * the end of the range is referencing past the last valid SIMD pack accessible
      in the original range.

    Such clamped range is then safe to be iterated using aligned_iterator while
    the remaining elements of the original range can be processed using regular
    scalar iterators.

    @tparam C Width of the SIMD register to use as iteration value.
    @param begin A Range addressing a contiguous memory block
    @param end

    @return An instance of realigned_input_range
  **/
  template<std::size_t C, typename Iterator> inline
  iterator_range<aligned_input_iterator<Iterator, C> >
  realigned_input_range( Iterator begin, Iterator end )
  {
    typedef typename std::iterator_traits<Iterator>::value_type type;

    // Offset to aligned begin
    type const* ptr     = &(*begin);
    type const* new_ptr = align_on(ptr, C*sizeof(type));
    std::size_t db      = std::distance(ptr,new_ptr);

    // Size in equivalent SIMD register
    std::size_t sz = ((std::distance(begin,end)-db)/C)*C;

    return aligned_input_range<C>( begin + db, begin + db + sz );
  }

  template<typename Iterator> inline
  iterator_range< aligned_input_iterator<Iterator> >
  realigned_input_range( Iterator begin, Iterator end )
  {
    typedef typename std::iterator_traits<Iterator>::value_type type;
    return realigned_input_range<pack<type>::static_size>(begin,end);
  }

  template<std::size_t C, typename Range> inline
  iterator_range<aligned_input_iterator<typename range_iterator<Range const>::type,C> >
  realigned_input_range( Range const& r )
  {
    return realigned_input_range<C>( boost::begin(r), boost::end(r) );
  }

  template<typename Range> inline
  iterator_range<aligned_input_iterator<typename range_iterator<Range const>::type> >
  realigned_input_range( Range const& r )
  {
    return realigned_input_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
