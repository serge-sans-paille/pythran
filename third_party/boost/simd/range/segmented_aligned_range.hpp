//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_SEGMENTED_ALIGNED_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_SEGMENTED_ALIGNED_RANGE_HPP_INCLUDED

#include <boost/simd/range/aligned_range.hpp>
#include <boost/simd/range/detail/segment.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/align/align_up.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  /*!
    @ingroup group-range
    @defgroup ranges-segmented_aligned_range_t segmented_aligned_range_t (alias template)

    Utility meta-function that computes the type of a segmented aligned SIMD range from an
    @cppconcept{Iterator} type and cardinal.

    @par Description

    1.  @code
        template<typename Iterator, std::size_t N>
        using segmented_aligned_range_t = implementation-defined;
        @endcode

    2.  @code
        template<typename Iterator>
        using segmented_aligned_range_t = implementation-defined;
        @endcode

    This type is mostly used to generate a type suitable for function template argument matching.
    Result of calling [boost::simd::segmented_aligned_range](@ref ranges-segmented_aligned_range)
    can be stored in an @c auto variable and used directly.

    [boost::simd::segmented_aligned_range_t](@ref ranges-segmented_aligned_range_t) provides three
    members that encapsulates the three SIMD-aware segments of a given Range. Let's @c r be an
    instance of @c segmented_aligned_range_t<Iterator,N>. The following members are then defined:

      - @c head which is a Range referencing the scalar values between the beginning of the original
        range and the first value able to be Vectorized.
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
      - @ref ranges-segmented_range_t

    @par Example
    @snippet segmented_aligned_range_t.cpp segmented_aligned_range_t

    Possible output

    @snippet segmented_aligned_range_t.txt segmented_aligned_range_t
  **/


  /*!
    @ingroup group-range
    @defgroup ranges-segmented_aligned_range segmented_aligned_range (function template)

    Range adapter that allow aligned traversal of data as value of both Vectorizable and Vectorized
    types.

    @headerref{<boost/simd/range/segmented_aligned_range.hpp>}

    @par Description

    1.  @code
        template<typename Integral, class Iterator>
        segmented_aligned_range_t<Iterator, Integral::value> segmented_aligned_range(Iterator first, Iterator last, Integral const& card)
        @endcode

    2.  @code
        template<class Iterator>
        segmented_aligned_range_t<Iterator> segmented_aligned_range(Iterator first, Iterator last)
        @endcode

    3.  @code
        template<typename Integral, class Range>
        segmented_aligned_range_t<Iterator, N> segmented_aligned_range(Range&& r, Integral const& card)
        @endcode

    4.  @code
        template<typename Range>
        segmented_aligned_range_t<Iterator> segmented_aligned_range(Range&& r)
        @endcode

    1.  Adapt the range @range{first,last} into a segmented aligned range over Vectorized type of
        cardinal @c Integral::value.

    2.  Adapt the range @range{first,last} into a segmented aligned range over Vectorized type of default cardinal.

    3.  Adapt the range @range{r.begin(), r.end()} into a segmented aligned range over Vectorized type of
        cardinal @c Integral::value.

    4.  Adapt the range @range{r.begin(), r.end()} into a segmented aligned range over Vectorized type of
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
    scalar or SIMD operations. Iteration over said data are performed using aligned load and store
    operations.

    @par Requirements
    - **first**, **last**, **r.begin()**, **r.end()** must be @c ContiguousIterator
      to Vectorizable type.
    - <tt>std::distance(first,last)</tt> is an exact multiple of @c card::value

    @par Related components
      - @ref ranges-range_t
      - @ref ranges-aligned_range
      - @ref ranges-segmented_range

    @par Example
    @snippet segmented_aligned_range.cpp segmented_aligned_range

    Possible output

    @snippet segmented_aligned_range.txt segmented_aligned_range
  **/

  template< typename Iterator
          , std::size_t N = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  using segmented_aligned_range_t = detail::segment_<Iterator,detail::aligned_iterator<Iterator,N>>;

  // Iterators + specific cardinal
  template<typename Iterator, std::size_t N>
  BOOST_FORCEINLINE segmented_aligned_range_t<Iterator,N>
  segmented_aligned_range(Iterator b, Iterator e, nsm::uint64_t<N> const& card)
  {
    using result_t = detail::segment_<Iterator, detail::aligned_iterator<Iterator,N>>;
    auto alg = pack<typename std::iterator_traits<Iterator>::value_type,N>::alignment;

    // How many data in the range
    std::size_t sz = std::distance(b, e);

    // Compute the pointer to the beginning of the aligned zone inside r
    auto p = &(*b);
    auto a = reinterpret_cast<decltype(p)>( alignment::align_up( reinterpret_cast<std::uintptr_t>(p)
                                                               , alg
                                                               )
                                          );

    // Next aligned address may be out of range, so make sure psz is not bigger than sz
    std::size_t psz = std::min<std::size_t>(sz,std::distance(p, a));

    // How many data are inside the SIMD body
    //std::size_t msz = (sz >= psz) ? (N * ((sz - psz) / N)) : (0u);
    std::size_t msz = (sz >= psz) ? (N * ((sz - psz) / N)) : (0u);

    // Head/Body/Tail frontiers
    auto has_body = (msz != 0u);
    auto he = has_body ? b  + psz : e;
    auto be = has_body ? he + msz : e;
    auto te = has_body ? be       : e;

    return result_t { iterator_range<Iterator>(b,he)
                    , aligned_range(he,be,card)
                    , iterator_range<Iterator>(te,e)
                    };
  }

  // Iterators + default cardinal
  template<typename Iterator>
  BOOST_FORCEINLINE segmented_aligned_range_t<Iterator>
  segmented_aligned_range(Iterator b, Iterator e)
  {
    using value_t = typename std::iterator_traits<Iterator>::value_type;
    return segmented_aligned_range(b,e, nsm::uint64_t<pack<value_t>::static_size>());
  }

  // Range + specific cardinal
  template<std::size_t N, typename Range>
  BOOST_FORCEINLINE segmented_aligned_range_t<detail::range_iterator<Range>,N>
  segmented_aligned_range( Range&& r, nsm::uint64_t<N> const& card )
  {
    return segmented_aligned_range( tt::begin(std::forward<Range>(r))
                                  , tt::end(std::forward<Range>(r))
                                  , card
                                  );
  }

  // Range + default cardinal
  template<typename Range>
  BOOST_FORCEINLINE segmented_aligned_range_t<detail::range_iterator<Range>>
  segmented_aligned_range( Range&& r )
  {
    return segmented_aligned_range( tt::begin(std::forward<Range>(r))
                                  , tt::end(std::forward<Range>(r))
                                  );
  }
} }

#endif
