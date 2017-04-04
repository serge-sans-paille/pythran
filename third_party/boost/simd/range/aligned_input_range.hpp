//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_ALIGNED_INPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_ALIGNED_INPUT_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/aligned_input_iterator.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @ingroup group-std
    Builds an Input ContiguousRange that iterates over the original <tt>[begin, end[</tt>
    ContiguousRange by returning boost::simd::pack at every iteration step.

    @par Example
    @snippet aligned_input_range.cpp aligned_input_range
    Possible output:
    @code
    Sum of [1 ... 16] is 136
    @endcode

    @pre @c std::distance(begin,end) is an exact multiple of @c N
    @pre @c std::addressof(*begin) is aligned on @c pack<Iterator::value_type,N>::alignment
    @tparam C Cardinal of the pack to be iterated. By default, @c N is equal to the native cardinal
            on current architecture.
    @param begin Starting iterator of the ContiguousRange to adapt
    @param end   End iterator of the ContiguousRange to adapt
    @return An Input ContiguousRange returning boost::simd::pack
  **/
  template<std::size_t C, typename Iterator> inline
#if !defined(DOXYGEN_ONLY)
  boost::iterator_range<detail::aligned_input_iterator<Iterator, C> >
#else
  auto
#endif
  aligned_input_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(begin,end), C)
    , "ContiguousRange being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_input_begin<C>(begin)
                                      , detail::aligned_input_end<C>(end)
                                      );
  }

  template<typename Iterator> inline
  boost::iterator_range< detail::aligned_input_iterator<Iterator> >
  aligned_input_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned ( std::distance(begin,end)
                                      , detail::aligned_input_iterator<Iterator>::cardinal
                                      )
    , "ContiguousRange being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_input_begin(begin)
                                      , detail::aligned_input_end(end)
                                      );
  }

  /*!
    @ingroup group-std
    Builds an Input ContiguousRange that iterates over the original ContiguousRange by
    returning boost::simd::pack at every iteration step.

    @pre @c std::distance(begin,end) is an exact multiple of @c N
    @pre @c &(*begin) is aligned on @c pack<ContiguousRange::value_type,N>::alignment
    @tparam N Cardinal of the pack to be iterated. By default, @c N is equal to
              the native cardinal of current architecture.
    @param r Input ContiguousRange to adapt
    @return An Input ContiguousRange returning boost::simd::pack of cardinal @c N
  **/
  template<std::size_t C, typename ContiguousRange> inline
#if !defined(DOXYGEN_ONLY)
  boost::iterator_range<detail::aligned_input_iterator<typename range_iterator<ContiguousRange const>::type,C>>
#else
  auto
#endif
  aligned_input_range( ContiguousRange const& r )
  {
    return aligned_input_range<C>( boost::begin(r), boost::end(r) );
  }

  template<typename ContiguousRange> inline
  boost::iterator_range<detail::aligned_input_iterator<typename range_iterator<ContiguousRange const>::type>>
  aligned_input_range( ContiguousRange const& r )
  {
    return aligned_input_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
