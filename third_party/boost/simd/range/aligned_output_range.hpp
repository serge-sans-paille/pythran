//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_ALIGNED_OUTPUT_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/aligned_output_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    @brief Adapt a range of aligned data to be used as a SIMD output range

    Builds a Output Range that iterates over the original <tt>[begin, end[</tt> Range but
    returns pack values.

    @pre @c std::distance(begin,end) is an exact multiple of @c N
    @pre @c &(*begin) is aligned on @c pack<Iterator::value_type,N>::alignment

    @tparam N Cardinal of the pack to be iterated. By default, @c N is equal to
              the native cardinal of current architecture.

    @param begin Starting iterator of the Range to adapt
    @param end   End iterator of the Range to adapt

    @return An Output Range returning SIMD pack o cardinal @c N
  **/
  template<std::size_t C, class Iterator> inline
  boost::iterator_range< detail::aligned_output_iterator<Iterator, C> >
  aligned_output_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(begin,end), C)
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_output_begin<C>(begin)
                                      , detail::aligned_output_end<C>(end)
                                      );
  }

  /// @overload
  template<class Iterator> inline
  boost::iterator_range< detail::aligned_output_iterator<Iterator> >
  aligned_output_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned( std::distance(begin,end)
                , detail::aligned_output_iterator<Iterator>::cardinal
                )
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_output_begin(begin)
                                      , detail::aligned_output_end(end)
                                      );
  }

  /*!
    @ingroup group-api
    @brief Adapt a range of aligned data to be used as a SIMD output range

    Builds an Output Range that iterates over the original Range but returns pack values.

    @pre @c std::distance(begin,end) is an exact multiple of @c N
    @pre @c &(*std::begin(r)) is aligned on @c pack<Range::value_type,N>::alignment

    @tparam N Cardinal of the pack to be iterated. By default, @c N is equal to
              the native cardinal of current architecture.

    @param r Output Range to adapt

    @return An Output Range returning SIMD pack o cardinal @c N
  **/
  template<std::size_t C, class Range> inline
  boost::iterator_range<detail::aligned_output_iterator<typename range_iterator<Range>::type,C> >
  aligned_output_range( Range& r )
  {
    return aligned_output_range<C>( boost::begin(r), boost::end(r) );
  }

  /// @overload
  template<class Range> inline
  boost::iterator_range<detail::aligned_output_iterator<typename range_iterator<Range>::type> >
  aligned_output_range( Range& r )
  {
    return aligned_output_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
