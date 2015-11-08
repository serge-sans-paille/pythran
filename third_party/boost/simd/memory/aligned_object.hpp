//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OBJECT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OBJECT_HPP_INCLUDED

#include <boost/simd/preprocessor/new.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief Imbue a type with aligned new and delete overloads

    When used as a base class, aligned_object adds overloaded new and delete
    operators that use aligned allocation function over an arbitrary alignment
    boundary @c Alignment.

    @usage{memory/aligned_object.cpp}

    @tparam Alignment Alignment boundary in bytes to use for dynamic allocation
            of child type.
  **/

  #ifdef BOOST_SIMD_COMPILER_MSVC
  #pragma warning( push )
  #pragma warning( disable : 4324 )
  #endif
  template<std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  BOOST_SIMD_ALIGNED_TYPE_ON_MPL(struct, Alignment) aligned_object
  {
    public:

    /**
      @brief Static integral constant containing current alignment constraints

      alignment_value gives access to the alignment constraint from the
      child type.
     */
    static const std::size_t alignment_value = Alignment;

    #if !defined(DOXYGEN_ONLY)
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(Alignment)
    #endif
  };
  #ifdef BOOST_SIMD_COMPILER_MSVC
  #pragma warning( pop )
  #endif
} } }

namespace boost { namespace simd
{
  using meta::aligned_object;
} }

#endif
