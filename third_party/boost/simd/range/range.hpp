//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/iterator.hpp>
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
    @defgroup ranges-range_t range_t (alias template)

    Utility meta-function that computes the type of an unaligned SIMD range from an
    @cppconcept{Iterator} type and cardinal.

    @par Description

    1.  @code
        template<typename Iterator, std::size_t N>
        using range_t = implementation-defined;
        @endcode

    2.  @code
        template<typename Iterator>
        using range_t = implementation-defined;
        @endcode

    This type is mostly used to generate a type suitable for function template argument matching.
    Result of calling [boost::simd::range](@ref ranges-range) can be stored in an @c auto variable
    and used directly.

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
      - @ref ranges-range
      - @ref ranges-aligned_range_t

    @par Example
    @snippet range_t.cpp range_t

    Possible output

    @snippet range_t.txt range_t
  **/

  /*!
    @ingroup group-range
    @defgroup ranges-range range (function template)

    Range adapter that allow traversal of data as value of Vectorized type.

    @headerref{<boost/simd/range/range.hpp>}

    @par Description

    1.  @code
        template<typename Integral, class Iterator>
        range_t<Iterator, Integral::value> range(Iterator first, Iterator last, Integral const& card)
        @endcode

    2.  @code
        template<class Iterator>
        range_t<Iterator> range(Iterator first, Iterator last)
        @endcode

    3.  @code
        template<typename Integral, class Range>
        range_t<Iterator, N> range(Range&& r, Integral const& card)
        @endcode

    4.  @code
        template<typename Range>
        range_t<Iterator> range(Range&& r)
        @endcode

    1.  Adapt the range @range{first,last} into a range over Vectorized type of
        cardinal @c Integral::value.

    2.  Adapt the range @range{first,last} into a range over Vectorized type of default cardinal.

    3.  Adapt the range @range{r.begin(), r.end()} into a range over Vectorized type of
        cardinal @c Integral::value.

    4.  Adapt the range @range{r.begin(), r.end()} into a range over Vectorized type of
        default cardinal

    @par Parameters

    | Name                | Description                                                             |
    |--------------------:|:------------------------------------------------------------------------|
    | **first**, **last** | pair of @c ContiguousIterator defining the range of elements to adapt   |
    | **r**               | the range of elements to adapt                                          |
    | **card**            | an @intconst representing the desired Vectorized type cardinal          |

    @par Return Value
    A @c ContiguousRange which can be used to iterate over the data stored in the original
    range by returning boost::simd::pack of chosen cardinal as dereferenced data.
    Iteration over said data are performed using unaligned load and store operations.

    @par Requirements
    - **first**, **last**, **r.begin()**, **r.end()** must be @c ContiguousIterator
      to Vectorizable type.
    - <tt>std::distance(first,last)</tt> is an exact multiple of @c card::value

    @par Related components
      - @ref ranges-range_t
      - @ref ranges-aligned_range

    @par Example
    @snippet range.cpp range

    Possible output

    @snippet range.txt range
  **/

  // Type of range
  template< typename Iterator
          , std::size_t N = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  using range_t = boost::iterator_range<detail::iterator<Iterator,N>>;


  // Iterator range + Cardinal
  template< typename Iterator
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE range_t<Iterator, Integral::value>
  range( Iterator first, Iterator last, Integral const& )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned(std::distance(first,last), Integral::value)
    , "Adapted ContiguousRange does not hold an integral number of SIMD pack."
    );

    return boost::make_iterator_range ( detail::begin<Integral::value>(first)
                                      , detail::end<Integral::value>(last)
                                      );
  }

  // Iterator range
  template<class Iterator>
  BOOST_FORCEINLINE range_t<Iterator> range( Iterator first, Iterator last )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::detail::is_aligned ( std::distance(first,last)
                                      , detail::iterator<Iterator>::cardinal
                                      )
    , "Adapted ContiguousRange does not hold an integral number of SIMD pack."
    );

    return boost::make_iterator_range( detail::begin(first), detail::end(last) );
  }

  // Actual range + Cardinal
  template< typename ContiguousRange
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE range_t<typename range_iterator<ContiguousRange>::type,Integral::value>
  range( ContiguousRange&& r, Integral const& card )
  {
    return range( tt::begin(std::forward<ContiguousRange>(r))
                , tt::end  (std::forward<ContiguousRange>(r))
                , card
                );
  }

  // Actual range
  template<class ContiguousRange>
  BOOST_FORCEINLINE range_t<typename range_iterator<ContiguousRange>::type>
  range( ContiguousRange&& r )
  {
    return range( tt::begin(std::forward<ContiguousRange>(r))
                , tt::end  (std::forward<ContiguousRange>(r))
                );
  }
} }

#endif
