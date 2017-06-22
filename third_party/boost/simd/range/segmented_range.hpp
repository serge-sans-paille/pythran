//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_SEGMENTED_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_SEGMENTED_RANGE_HPP_INCLUDED

#include <boost/simd/range/range.hpp>
#include <boost/simd/range/detail/segment.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/align/align_down.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  /*!
    @ingroup group-range
    @defgroup ranges-segmented_range_t segmented_range_t (alias template)

    Utility meta-function that computes the type of a segmented unaligned SIMD range from an
    @cppconcept{Iterator} type and cardinal.

    @par Description

    1.  @code
        template<typename Iterator, std::size_t N>
        using segmented_range_t = implementation-defined;
        @endcode

    2.  @code
        template<typename Iterator>
        using segmented_range_t = implementation-defined;
        @endcode

    This type is mostly used to generate a type suitable for function template argument matching.
    Result of calling [boost::simd::segmented_range](@ref ranges-segmented_range) can be stored in
    an @c auto variable and used directly.

    [boost::simd::segmented_range_t](@ref ranges-segmented_range_t) provides three members that
    encapsulates the three SIMD-aware segments of a given Range. Let's @c r be an instance of
    @c segmented_range_t<Iterator,N>. The following members are then defined:

      - @c head which is a Range referencing the scalar values between the beginning of the original range
        and the first value able to be Vectorized. As [boost::simd::segmented_range_t](@ref ranges-segmented_range_t)
        uses unaligned load and store, this Range is always empty but is provided so generic code
        between [boost::simd::segmented_range_t](@ref ranges-segmented_range_t) and
        [boost::simd::segmented_aligned_range_t](@ref ranges-segmented_aligned_range_t).
      - @c body which is a [boost::simd::range_t](@ref ranges-range_t) over the Vectorizable part of
        the original Range.
      - @c tail which is a Range referencing the left over scalar values after the last Vectorized
        data.

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
      - @ref ranges-range_t
      - @ref ranges-aligned_range_t
      - @ref ranges-segmented_aligned_range_t

    @par Example
    @snippet segmented_range_t.cpp segmented_range_t

    Possible output

    @snippet segmented_range_t.txt segmented_range_t

    Note hwo the first loop over @c .head yields an empty line.
  **/

  /*!
    @ingroup group-range
    @defgroup ranges-segmented_range segmented_range (function template)

    Range adapter that allow traversal of data as value of both Vectorizable and Vectorized types.

    @headerref{<boost/simd/range/segmented_range.hpp>}

    @par Description

    1.  @code
        template<typename Integral, class Iterator>
        segmented_range_t<Iterator, Integral::value> segmented_range(Iterator first, Iterator last, Integral const& card)
        @endcode

    2.  @code
        template<class Iterator>
        segmented_range_t<Iterator> segmented_range(Iterator first, Iterator last)
        @endcode

    3.  @code
        template<typename Integral, class Range>
        segmented_range_t<Iterator, N> segmented_range(Range&& r, Integral const& card)
        @endcode

    4.  @code
        template<typename Range>
        segmented_range_t<Iterator> segmented_range(Range&& r)
        @endcode

    1.  Adapt the range @range{first,last} into a segmented range over Vectorized type of
        cardinal @c Integral::value.

    2.  Adapt the range @range{first,last} into a segmented range over Vectorized type of default cardinal.

    3.  Adapt the range @range{r.begin(), r.end()} into a segmented range over Vectorized type of
        cardinal @c Integral::value.

    4.  Adapt the range @range{r.begin(), r.end()} into a segmented range over Vectorized type of
        default cardinal

    @par Parameters

    | Name                | Description                                                             |
    |--------------------:|:------------------------------------------------------------------------|
    | **first**, **last** | pair of @c ContiguousIterator defining the range of elements to adapt   |
    | **r**               | the range of elements to adapt                                          |
    | **card**            | an @intconst representing the desired Vectorized type cardinal          |

    @par Return Value
    A implementation-defined structure which contains three sub-ranges covering the head, body and
    tail of the original range so that iteration over each sub-ranges is performed with the proper
    scalar or SIMD operations. Iteration over said data are performed using unaligned load and store
    operations.

    @par Requirements
    - **first**, **last**, **r.begin()**, **r.end()** must be @c ContiguousIterator
      to Vectorizable type.
    - <tt>std::distance(first,last)</tt> is an exact multiple of @c card::value

    @par Related components
      - @ref ranges-range_t
      - @ref ranges-aligned_range
      - @ref ranges-segmented_aligned_range

    @par Example
    @snippet segmented_range.cpp segmented_range

    Possible output

    @snippet segmented_range.txt segmented_range
  **/

  // Segmented range type
  template< typename Iterator
          , std::size_t N = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  using segmented_range_t = detail::segment_<Iterator, detail::iterator<Iterator,N>>;

  // Itertor + specific cardinal
  template< typename Iterator
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE segmented_range_t<Iterator,Integral::value>
  segmented_range(Iterator b, Iterator e, Integral const& card)
  {
    /*
      When dealing with unaligned range adaptation, we know there is no head.
      We just need to compute where the original range stops in terms of packs.
    */
    auto alg = pack<typename std::iterator_traits<Iterator>::value_type,Integral::value>::static_size;
    std::size_t vz = alignment::align_down(std::distance(b, e),alg);

    return segmented_range_t<Iterator,Integral::value>{ iterator_range<Iterator>()
                                                      , range(b,b+vz, card)
                                                      , iterator_range<Iterator>(b+vz,e)
                                                      };
  }

  // Iterator + default cardinal
  template<typename Iterator>
  BOOST_FORCEINLINE segmented_range_t<Iterator> segmented_range(Iterator b, Iterator e)
  {
    using value_t = typename std::iterator_traits<Iterator>::value_type;
    return segmented_range(b,e, nsm::uint64_t<pack<value_t>::static_size>());
  }

  // Range + specific cardinal
  template< typename Range
          , typename Integral
          // SFINAE out if Integral is not modeling IntegralConstant
          , typename = nsm::constant<typename Integral::value_type,Integral::value>
          >
  BOOST_FORCEINLINE segmented_range_t<detail::range_iterator<Range>,Integral::value>
  segmented_range( Range&& r, Integral const& card )
  {
    return segmented_range( tt::begin(std::forward<Range>(r)), tt::end(std::forward<Range>(r))
                          , card
                          );
  }

  // Range + default cardinal
  template<typename Range>
  BOOST_FORCEINLINE segmented_range_t<detail::range_iterator<Range>>
  segmented_range( Range&& r )
  {
    return segmented_range( tt::begin(std::forward<Range>(r)), tt::end(std::forward<Range>(r)) );
  }
} }

#endif
