//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/details/uncheck_iterator.hpp>
#include <boost/simd/memory/details/output_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Write-only SIMD iterator

    aligned_output_iterator adapt a pointer to aligned memory into a standard
    compliant iterator that traverses this memory block using SIMD registers.

    @par Models:

    @model{ http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
          , RandomAccessIterator
          }

    @usage_output{memory/aligned_output_iterator.cpp,memory/aligned_output_iterator.out}

    @tparam T Type pointed to by the iterator
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
  struct  aligned_output_iterator
        : details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::aligned_store_
                  >
  {
    typedef details::output_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::aligned_store_
                  >                                               parent;

    /// Default constructor
    aligned_output_iterator() : parent() {}

    /// Constructor from an aligned pointer
    explicit  aligned_output_iterator(Iterator p) : parent(p)
    {
      // MSVC SCL_SECURE mode adds extra-check that make aligned end
      // difficult to check with this.
      typename details::unchecker<Iterator>::type lp = details::unchecker<Iterator>::call(p);
      boost::dispatch::ignore_unused(lp);

      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(&(*lp) , C*sizeof(*lp) )
      , "The constructor of iterator<T,C> has been called on a pointer "
        "which alignment is not compatible with the current SIMD extension."
      );
    }

    /// INTERNAL ONLY
    aligned_output_iterator( parent const& src ) : parent(src) {}
  };

  /*!
    @brief Adapter for aligned SIMD write-only iterator

    Convert an existing iterator referencing the beginning of a aligned memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/aligned_output_iterator.cpp,memory/aligned_output_iterator.out}

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of aligned_output_iterator
  **/
  template<typename Iterator> inline
  aligned_output_iterator<Iterator> aligned_output_begin(Iterator p)
  {
    return aligned_output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for aligned SIMD write-only iterator

    Convert an existing iterator referencing the beginning of a aligned memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/aligned_output_iterator.cpp,memory/aligned_output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the beginning of a contiguous memory block.

    @return An instance of aligned_output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  aligned_output_iterator<Iterator,C> aligned_output_begin(Iterator p)
  {
    return aligned_output_iterator<Iterator,C>(p);
  }

  /*!
    @brief Adapter for aligned SIMD write-only iterator

    Convert an existing iterator referencing the end of a aligned memory
    block into a SIMD aware write-only iterator returning SIMD pack of optimal
    cardinal for current architecture.

    @usage_output{memory/aligned_output_iterator.cpp,memory/aligned_output_iterator.out}

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of aligned_output_iterator
  **/
  template<typename Iterator> inline
  aligned_output_iterator<Iterator> aligned_output_end(Iterator p)
  {
    return aligned_output_iterator<Iterator>(p);
  }

  /*!
    @brief Adapter for aligned SIMD write-only iterator

    Convert an existing iterator referencing the end of a aligned memory
    block into a SIMD aware write-only iterator returning SIMD pack of cardinal
    @c C.

    @usage_output{memory/aligned_output_iterator.cpp,memory/aligned_output_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p An iterator referencing the end of a contiguous memory block.

    @return An instance of aligned_output_iterator
  **/
  template<std::size_t C, typename Iterator> inline
  aligned_output_iterator<Iterator,C> aligned_output_end(Iterator p)
  {
    return aligned_output_iterator<Iterator,C>(p);
  }
} }

#endif
