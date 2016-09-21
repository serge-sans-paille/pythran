//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_SEGMENTED_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_SEGMENTED_RANGE_HPP_INCLUDED

#include <boost/simd/range/aligned_output_range.hpp>
#include <boost/align/align_up.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost { namespace simd { namespace detail
{
  template < std::size_t C
           , typename AlignedIterator
           , typename Iterator
           , typename MakeAlignedRange
           >
  std::tuple< iterator_range<Iterator>
            , iterator_range<AlignedIterator>
            , iterator_range<Iterator>
            >
  inline segmented_range( Iterator b, Iterator e, MakeAlignedRange make_aligned_range )
  {
    // Expected alignment
    auto alg = pack<typename std::iterator_traits<Iterator>::value_type, C>::alignment;

    // Compute the pointer to the beginning of the aligned zone inside r
    auto const*  p = &(*b);
    auto const* ap =
      reinterpret_cast<decltype(p)>(alignment::align_up(reinterpret_cast<std::size_t>(p), alg));

    std::size_t  sz = std::distance(b, e);
    // Next aligned address may be out of range, so make sure psz is not bigger than sz
    std::size_t psz = std::min(sz, static_cast<std::size_t>(std::distance(p, ap)));
    std::size_t msz = (sz >= psz) ? (C * ((sz - psz) / C)) : (0u);

    auto pib = b;
    auto mib = b + psz;
    auto eib = b + psz + msz;

    auto pie = mib;
    auto mie = eib;
    auto eie = b + sz;

    if (msz == 0u) {
      // Any well-designed iterators should be default-constructible
      mib = Iterator();
      mie = Iterator();
    }

    // Build the segmented stuff
    return std::make_tuple( make_iterator_range(pib, pie)
                          ,  make_aligned_range(mib, mie)
                          , make_iterator_range(eib, eie)
                          );
  }

} } }

#endif
