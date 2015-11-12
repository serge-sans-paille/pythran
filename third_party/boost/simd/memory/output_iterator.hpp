//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/details/output_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @brief Write-only SIMD iterator

    output_iterator adapt an Iterator into a standard compliant iterator that
    traverses this memory block using SIMD registers.

    @par Models:

    @model{ http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
          , RandomAccessIterator
          }

    @usage_output{memory/output_iterator.cpp,memory/output_iterator.out}

    @tparam Iterator Iterator type to adapt
    @tparam C Width of the SIMD register to use as iteration value. By default
              this value is equal to the optimal register cardinal for current
              architecture and type @c T.
  **/
  template< typename Iterator
          , std::size_t C = meta::cardinal_of
                            < pack< typename std::iterator_traits<Iterator>
                                                ::value_type
                                  >
                            >::value
          >
  struct  output_iterator
        : details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::store_
                  >
  {
    typedef details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::store_
                  >                                           parent;

    /// Default constructor
    output_iterator() : parent() {}

    /// INTERNAL ONLY
    output_iterator( parent const& src ) : parent(src) {}

    /// Constructor from an aligned pointer
    explicit  output_iterator(Iterator p) : parent(p) {}
  };

  /*!
    @brief Adapter for SIMD write-only iterator

    Convert an existing iterator referencing the beginning of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/output_iterator.cpp,memory/output_iterator.out}

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of output_iterator
  **/
  template<typename Iterator> inline
  output_iterator<Iterator> output_begin(Iterator p)
  {
    return output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for SIMD write-only iterator

    Convert an existing iterator referencing the beginning of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/output_iterator.cpp,memory/output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  output_iterator<Iterator, C> output_begin(Iterator p)
  {
    return output_iterator<Iterator, C>(p);
  }

  /*!
    @brief Adapter for SIMD write-only iterator

    Convert an existing iterator referencing the end of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/output_iterator.cpp,memory/output_iterator.out}

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of output_iterator
  **/
  template<typename Iterator> inline
  output_iterator<Iterator> output_end(Iterator p)
  {
    return output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for SIMD write-only iterator

    Convert an existing iterator referencing the end of a contiguous memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/output_iterator.cpp,memory/output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  output_iterator<Iterator,C> output_end(Iterator p)
  {
    return output_iterator<Iterator, C>(p);
  }
} }

#endif
