//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_ALIGNED_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_ALIGNED_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/aligned_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  /*!
    @ingroup group-range
    @defgroup ranges-aligned_range_t aligned_range_t (alias template)

    Utility meta-function that computes the type of an aligned SIMD range from
    an @cppconcept{Iterator} type and cardinal.

    @par Description

    1.  @code
        template<typename Iterator, std::size_t N>
        using aligned_range_t = implementation-defined;
        @endcode

    2.  @code
        template<typename Iterator>
        using aligned_range_t = implementation-defined;
        @endcode

    This type is mostly used to generate a type suitable for function template argument matching.
    Result of calling [boost::simd::aligned_range](@ref ranges-aligned_range) can be stored in a
    @c auto variable and used directly.

    @par Type Parameters

    | Name         | Description                                                  |
    |-------------:|:-------------------------------------------------------------|
    | **Iterator** | Underlying @cppconcept{Iterator} type of the range to adapt  |
    | **N**        | Cardinal of the Vectorized type to iterate over              |

    @par Type Requirements
    - **Iterator** must be a @c ContiguousIterator to Vectorizable type.
    - If specified, **N** must be a non-zero power of two. Otherwise, it defaults to
      <tt>pack<iterator_traits<Iterator>::type>::static_size</tt>.

    @par Related components
      - @ref ranges-aligned_range
      - @ref ranges-range_t

    @par Example
    @snippet aligned_range_t.cpp aligned_range_t

    Possible output

    @snippet aligned_range_t.txt aligned_range_t
  **/

  /*!
    @ingroup group-range
    @defgroup ranges-aligned_range aligned_range (function template)

    Range adapter that allow aligned traversal of data as value of Vectorized type from aligned data.

    @headerref{<boost/simd/range/aligned_range.hpp>}

    @par Description

    1.  @code
        template<typename Integral, class Iterator>
        aligned_range_t<Iterator, Integral::value> aligned_range(Iterator first, Iterator last, Integral const& card)
        @endcode

    2.  @code
        template<class Iterator>
        aligned_range_t<Iterator> aligned_range(Iterator first, Iterator last)
        @endcode

    3.  @code
        template<typename Integral, class Range>
        aligned_range_t<Iterator, N> aligned_range(Range&& r, Integral const& card)
        @endcode

    4.  @code
        template<typename Range>
        aligned_range_t<Iterator> aligned_range(Range&& r)
        @endcode

    1.  Adapt the range @range{first,last} into an aligned_range over Vectorized type of
        cardinal @c Integral::value.

    2.  Adapt the range @range{first,last} into an aligned_range over Vectorized type of default cardinal.

    3.  Adapt the range @range{r.begin(), r.end()} into an aligned_range over Vectorized type of
        cardinal @c Integral::value.

    4.  Adapt the range @range{r.begin(), r.end()} into an aligned_range over Vectorized type of
        default cardinal

    @par Parameters

    | Name                | Description                                                            |
    |--------------------:|:-----------------------------------------------------------------------|
    | **first**, **last** | pair of @c ContiguousIterator defining the range of elements to adapt  |
    | **r**               | the range of elements to adapt                                         |
    | **card**            | an @intconst representing the desired Vectorized type cardinal         |

    @par Return Value
    A @c ContiguousRange which can be used to iterate over the data stored in the original
    aligned range by returning boost::simd::pack of chosen cardinal as dereferenced data.
    Iteration over said data are performed using aligned load and store operations.

    @par Requirements
    - **first**, **last**, **r.begin()**, **r.end()** must be @c ContiguousIterator
      to Vectorizable type.
    - <tt>std::distance(first,last)</tt> is an exact multiple of @c  card::value

    @par Related components
      - @ref ranges-aligned_range_t
      - @ref ranges-range

    @par Example
    @snippet aligned_range.cpp aligned_range

    Possible output

    @snippet aligned_range.txt aligned_range
  **/

  // Type of aligned_range
  template< typename Iterator
          , std::size_t N = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  using aligned_range_t = boost::iterator_range<detail::aligned_iterator<Iterator,N>>;

  // Iterators + cardinal
  template< typename Iterator
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE aligned_range_t<Iterator, Integral::value>
  aligned_range( Iterator first, Iterator last, Integral const& )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(first,last), Integral::value)
    , "ContiguousRange being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_begin<Integral::value>(first)
                                      , detail::aligned_end<Integral::value>(last)
                                      );
  }

  // Iterators
  template<typename Iterator> BOOST_FORCEINLINE
  aligned_range_t<Iterator> aligned_range( Iterator first, Iterator last )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned ( std::distance(first,last)
                                      , detail::aligned_iterator<Iterator>::cardinal
                                      )
    , "ContiguousRange being adapted holds a non integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::aligned_begin(first)
                                      , detail::aligned_end(last)
                                      );
  }

  // Range + cardinal
  template< typename ContiguousRange
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE aligned_range_t<typename range_iterator<ContiguousRange>::type,Integral::value>
  aligned_range( ContiguousRange&& r, Integral const& card )
  {
    return aligned_range( tt::begin(std::forward<ContiguousRange>(r))
                        , tt::end(std::forward<ContiguousRange>(r))
                        , card
                        );
  }

  // Range
  template<typename ContiguousRange>
  BOOST_FORCEINLINE aligned_range_t<typename range_iterator<ContiguousRange>::type>
  aligned_range( ContiguousRange&& r )
  {
    return aligned_range( tt::begin(std::forward<ContiguousRange>(r))
                        , tt::end(std::forward<ContiguousRange>(r))
                        );
  }
} }

#endif
