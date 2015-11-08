//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED

#include <boost/simd/memory/aligned_output_iterator.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Adapter for aligned SIMD write-only range

    Convert an existing range specified by two aligned iterators into a SIMD
    aware write-only iterator returning SIMD pack of optimal cardinal @c C.

    @usage_output{memory/aligned_output_range.cpp,memory/aligned_output_range.out}

    @tparam C Width of the SIMD register to use as iteration value.
    @param begin  A Range addressing a contiguous memory block
    @param end
    @return An instance of aligned_output_range
  **/
  template<std::size_t C, class Iterator> inline
  boost::iterator_range< aligned_output_iterator<Iterator, C> >
  aligned_output_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( is_aligned(std::distance(begin,end), C)
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( aligned_output_begin<C>(begin)
                                      , aligned_output_end<C>(end)
                                      );
  }

  /*!
    @brief Adapter for aligned SIMD write-only range

    Convert an existing range specified by two aligned iterators into a SIMD
    aware write-only iterator returning SIMD pack of optimal cardinal for
    current architecture.

    @usage_output{memory/aligned_output_range.cpp,memory/aligned_output_range.out}

    @param r A Range addressing a contiguous memory block

    @return An instance of aligned_output_range
  **/
  template<class Iterator> inline
  boost::iterator_range< aligned_output_iterator<Iterator> >
  aligned_output_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( is_aligned( std::distance(begin,end)
                , aligned_output_iterator<Iterator>::cardinal
                )
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( aligned_output_begin(begin)
                                      , aligned_output_end(end)
                                      );
  }

  /*!
    @brief Adapter for aligned SIMD write-only range

    Convert an existing range into a SIMD aware write-only iterator returning
    SIMD pack of cardinal @c C.

    @usage_output{memory/aligned_output_range.cpp,memory/aligned_output_range.out}

    @tparam C Width of the SIMD register to use as iteration value.
    @param r A Range addressing a contiguous memory block

    @return An instance of aligned_output_range
  **/
  template<std::size_t C, class Range> inline
  boost::iterator_range<aligned_output_iterator<typename range_iterator<Range>::type,C> >
  aligned_output_range( Range& r )
  {
    return aligned_output_range<C>( boost::begin(r), boost::end(r) );
  }

  /*!
    @brief Adapter for aligned SIMD write-only range

    Convert an existing range into a SIMD aware write-only iterator returning
    SIMD pack of optimal cardinal for current architecture.

    @usage_output{memory/aligned_output_range.cpp,memory/aligned_output_range.out}

    @param r A Range addressing a contiguous memory block

    @return An instance of aligned_output_range
  **/
  template<class Range> inline
  boost::iterator_range<aligned_output_iterator<typename range_iterator<Range>::type> >
  aligned_output_range( Range& r )
  {
    return aligned_output_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
