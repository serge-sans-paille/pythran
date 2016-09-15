//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_INPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_INPUT_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/input_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    @brief Adapt a range to be used as a SIMD input range

    Builds an Input Range that iterates over the original <tt>[begin, end[</tt> Range but
    returns pack values.

    @pre @c std::distance(begin,end) is an exact multiple of @c N

    @tparam N Cardinal of the pack to be iterated. By default, @c N is equal to
              the native cardinal of current architecture.

    @param begin Starting iterator of the Range to adapt
    @param end   End iterator of the Range to adapt

    @return An Input Range returning SIMD pack o cardinal @c N
  **/
  template<std::size_t N, class Iterator> inline
  boost::iterator_range<detail::input_iterator<Iterator, N> >
  input_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(begin,end), N)
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range(detail::input_begin<N>(begin),detail::input_end<N>(end));
  }

  /// @overload
  template<class Iterator> inline
  boost::iterator_range< detail::input_iterator<Iterator> >
  input_range( Iterator begin, Iterator end )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(begin,end) , detail::input_iterator<Iterator>::cardinal)
    , "Range being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range( detail::input_begin(begin), detail::input_end(end) );
  }

  /*!
    @ingroup group-api
    @brief Adapt a range to be used as a SIMD input range

    Builds an Input Range that iterates over the original Range but returns pack values.

    @pre @c std::distance(begin,end) is an exact multiple of @c N

    @tparam N Cardinal of the pack to be iterated. By default, @c N is equal to
              the native cardinal of current architecture.

    @param r Range to adapt

    @return An Input Range returning SIMD pack o cardinal @c N
  **/
  template<std::size_t N, class Range> inline
  boost::iterator_range<detail::input_iterator<typename range_iterator<Range const>::type,N> >
  input_range( Range const& r )
  {
    return input_range<N>( boost::begin(r), boost::end(r) );
  }

  /// @overload
  template<class Range> inline
  boost::iterator_range<detail::input_iterator<typename range_iterator<Range const>::type> >
  input_range( Range const& r )
  {
    return input_range( boost::begin(r), boost::end(r) );
  }
} }

#endif
