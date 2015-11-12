//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DIRECT_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DIRECT_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/stream.hpp>
#include <boost/simd/memory/details/output_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd
{
/*!
    @brief Non-temporal store based iterator

    direct_output_iterator adapt a pointer into a standard compliant iterator
    that allow for non-temporal write to the referenced memory.

    @par Models:

    @model{ http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
          , RandomAccessIterator
          }

    @usage_output{memory/direct_output_iterator.cpp,memory/direct_output_iterator.out}

    @tparam T Type pointed to by the iterator
  **/
  template< typename Iterator
          , std::size_t C = meta::cardinal_of
                            < pack< typename std::iterator_traits<Iterator>
                                                ::value_type
                                  >
                            >::value
          >
  struct  direct_output_iterator
        : details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::stream_
                  >
  {
    typedef details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::stream_
                  >                                           parent;

    /// Default constructor
    direct_output_iterator() : parent() {}

    /// INTERNAL ONLY
    direct_output_iterator( parent const& src ) : parent(src) {}

    /// Constructor from an aligned pointer
    explicit  direct_output_iterator(Iterator p) : parent(p) {}
  };

  /*!
    @brief Adapter for SIMD non-temporal, write-only iterator

    Convert an existing iterator referencing the beginning of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/direct_output_iterator.cpp,memory/direct_output_iterator.out}

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of direct_output_iterator
  **/
  template<typename Iterator> inline
  direct_output_iterator<Iterator> direct_output_begin(Iterator p)
  {
    return direct_output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for SIMD non-temporal, write-only iterator

    Convert an existing iterator referencing the beginning of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/direct_output_iterator.cpp,memory/direct_output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of direct_output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  direct_output_iterator<Iterator, C> direct_output_begin(Iterator p)
  {
    return direct_output_iterator<Iterator, C>(p);
  }

  /*!
    @brief Adapter for SIMD non-temporal, write-only iterator

    Convert an existing iterator referencing the end of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/direct_output_iterator.cpp,memory/direct_output_iterator.out}

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of direct_output_iterator
  **/
  template<typename Iterator> inline
  direct_output_iterator<Iterator> direct_output_end(Iterator p)
  {
    return direct_output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for SIMD non-temporal, write-only iterator

    Convert an existing iterator referencing the end of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/direct_output_iterator.cpp,memory/direct_output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of direct_output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  direct_output_iterator<Iterator,C> direct_output_end(Iterator p)
  {
    return direct_output_iterator<Iterator, C>(p);
  }
} }

#endif
