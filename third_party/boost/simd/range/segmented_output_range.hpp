//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_SEGMENTED_OUTPUT_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_SEGMENTED_OUTPUT_RANGE_HPP_INCLUDED

#include <boost/simd/range/detail/segmented_range.hpp>
#include <boost/simd/range/aligned_output_range.hpp>
#include <boost/align/align_up.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/range/detail/util.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  /*!
    @ingroup group-std
    A three Contiguous Output Ranges tuple able to support mixed scalar and SIMD
    traversal.

    The three sub-ranges are stored into a std::tuple and covers:
    - the scalar prologue range, i.e the range defined between the original begin and the first
      location to be properly aligned to be read as a boost::simd::pack
    - the main SIMD range, i.e the range defined between the first location to be properly aligned
      to be read as a boost::simd::pack and the location after the last readable pack.
    - the scalar epilogue range, i.e the range defined between the location after the last readable
      pack and the original end.
  */
  template <typename Iterator>
  using segmented_output_range_type = std::tuple< iterator_range<Iterator>
                                                , iterator_range<detail::aligned_output_iterator<Iterator>>
                                                , iterator_range<Iterator>
                                                >;

  /*!
    @ingroup group-std
    Splits a ContiguousRange into  a @ref segmented_output_range_type.

    @param b  Starting iterator of the ContiguousRange to adapt
    @param e  End iterator of the ContiguousRange to adapt
    @return   A triplet of Output Range covering the scalar prologue, the SIMD main range and the scalar
              epilogue covering the same data than the original Range.
    @see segmented_output_range_type
  **/
  template<std::size_t C, typename Iterator>
  inline
  segmented_output_range_type<Iterator>
  segmented_output_range( Iterator b, Iterator e )
  {
    return detail::segmented_range<C, detail::aligned_output_iterator<Iterator>>
      ( b
      , e
      , [](Iterator bb, Iterator ee) { return aligned_output_range(bb, ee); }
      );
  }

  /*!
     @overload
  */
  template<std::size_t C, class Range>
  inline
  segmented_output_range_type<detail::range_iterator<Range>>
  segmented_output_range( Range& r )
  {
    return segmented_output_range<C>( tt::begin(r), tt::end(r) );
  }

  /*!
     @overload
  */
  template<class Iterator> 
  inline
  segmented_output_range_type<Iterator>
  segmented_output_range( Iterator begin, Iterator end )
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return segmented_output_range<pack<value_type>::static_size>( begin, end );
  }

  /*!
     @overload
  */
  template<class Range> 
  inline
  segmented_output_range_type<detail::range_iterator<Range>>
  segmented_output_range( Range& r )
  {
    return segmented_output_range( tt::begin(r), tt::end(r) );
  }
} }

#endif
