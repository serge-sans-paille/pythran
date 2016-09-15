//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_SEGMENTED_INPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_SEGMENTED_INPUT_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/segmented_range.hpp>
#include <boost/simd/range/aligned_input_range.hpp>
#include <boost/align/align_up.hpp>
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
  template<std::size_t C, typename Iterator>
  std::tuple< iterator_range<Iterator>
            , iterator_range<detail::aligned_input_iterator<Iterator>>
            , iterator_range<Iterator>
            >
  inline segmented_input_range( Iterator b, Iterator e )
  {
    return detail::segmented_range<C, detail::aligned_input_iterator<Iterator>>
      ( b
      , e
      , [](Iterator bb, Iterator ee) { return aligned_input_range(bb, ee); }
      );
  }

  /// @overload
  template<class Iterator> inline
  auto    segmented_input_range( Iterator begin, Iterator end )
      ->  decltype( segmented_input_range< pack< typename std::iterator_traits<Iterator>
                                                              ::value_type
                                                  >::static_size
                                            >( begin, end )
                  )
  {
    return  segmented_input_range< pack< typename std::iterator_traits<Iterator>
                                                    ::value_type
                                        >::static_size
                                  >( begin, end );
  }

  template<std::size_t C, class Range> inline
  auto    segmented_input_range( Range const& r )
      ->  decltype( segmented_input_range<C>( boost::begin(r), boost::end(r) ) )
  {
    return segmented_input_range<C>( boost::begin(r), boost::end(r) );
  }

  template<class Range> inline
  auto    segmented_input_range( Range const& r )
      ->  decltype( segmented_input_range( boost::begin(r), boost::end(r) ) )
  {
    return segmented_input_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
