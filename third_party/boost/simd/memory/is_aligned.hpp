//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_IS_ALIGNED_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the is_aligned function
**/

#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/memory/is_power_of_2.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Alignment predicate for integers and pointers

    Checks if a value or pointer is aligned on an arbitrary alignment boundary

    @par Semantic:

    For any integer @c v and @c a:

    @code
    bool r = is_aligned(v,a);
    @endcode

    is equivalent to

    @code
    bool r = (reinterpret_cast<std::size_t>(v) % a) == 0
    @endcode

    If @c a is not a power of two, an assertion is triggered.

    @usage{memory/is_aligned.cpp}

    @param value  Value to check
    @param align  Alignment boundary to check for. If unspecified, @c align is
                  equal to the current SIMD alignment.

    @return A boolean indicating if @c value is aligned on @c align
  **/
  BOOST_FORCEINLINE
  bool is_aligned ( std::size_t value
                  , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
                  )
  {
    BOOST_ASSERT_MSG
    ( boost::simd::is_power_of_2(align)
    , "Invalid alignment boundary. You tried to check if "
      "an address or a value is aligned on a non-power of 2 boundary."
    );

    return !(value & (align-1) );
  }

  /// @overload
  template<class T> BOOST_FORCEINLINE
  bool is_aligned ( T* ptr
                  , std::size_t align = BOOST_SIMD_CONFIG_ALIGNMENT
                  )
  {
    return boost::simd::is_aligned(reinterpret_cast<std::size_t>(ptr),align);
  }
} }

#endif
