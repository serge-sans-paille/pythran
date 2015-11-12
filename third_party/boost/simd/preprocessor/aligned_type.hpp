//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_ALIGNED_TYPE_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_ALIGNED_TYPE_HPP_INCLUDED

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/preprocessor/align_on.hpp>

/*!
  @brief Macro wrapper for SIMD aligned type

  Wraps a type @c T so that it is aligned on an arbitrary alignment constraint.

  @usage{preprocessor/aligned_type_on.cpp}

  @param T      Type to align on current SIMD alignment
  @param ALIGN  Alignment constraint to respect
**/
#define BOOST_SIMD_ALIGNED_TYPE_ON(T,ALIGN) T BOOST_SIMD_ALIGN_ON(ALIGN)

/*!
  @brief Macro wrapper for SIMD aligned type in template context

  Wraps a type @c T so that it is aligned on an arbitrary alignment constraint.
  This macro is to be used when the type to mark as aligned is dependent on a template.

  @par Rationale

  This variant is required as some older compiler don't accept alignment
  attribute applied on template parameters. In all other cases, it is equivalent
  to BOOST_SIMD_ALIGNED_TYPE_ON.
  If not supported, the type will not be aligned.

  @param T      Type to align on current SIMD alignment
  @param ALIGN  Alignment constraint to respect
**/
#define BOOST_SIMD_ALIGNED_TYPE_ON_TPL(T,ALIGN) BOOST_SIMD_ALIGNED_TYPE_ON(T,ALIGN)

// Not supported by GCC 4.2
#if defined(BOOST_SIMD_COMPILER_GCC) && (BOOST_SIMD_GCC_VERSION < 40300)
#undef BOOST_SIMD_ALIGNED_TYPE_ON_TPL
#define BOOST_SIMD_ALIGNED_TYPE_ON_TPL(T,ALIGN) T
#endif

/*!
  @brief Macro wrapper for SIMD aligned type with template alignment

  Wraps a type @c T so that it is aligned on an arbitrary alignment constraint.
  This macro is to be used when the alignment is dependent on a template.

  @par Rationale

  This variant is required as some older compiler don't accept alignment
  attribute as a template. In all other cases, it is equivalent
  to BOOST_SIMD_ALIGNED_TYPE_ON.
  If not supported, it will fall back to BOOST_SIMD_CONFIG_ALIGNMENT.

  @param T      Type to align on current SIMD alignment
  @param ALIGN  Alignment constraint to respect
**/
#define BOOST_SIMD_ALIGNED_TYPE_ON_MPL(T,ALIGN) BOOST_SIMD_ALIGNED_TYPE_ON(T,ALIGN)

// Not supported by GCC 4.2 nor MSVC
#if (defined(BOOST_SIMD_COMPILER_GCC) && (BOOST_SIMD_GCC_VERSION < 40300))     \
 || defined(BOOST_SIMD_COMPILER_MSVC)
#undef BOOST_SIMD_ALIGNED_TYPE_ON_MPL
#define BOOST_SIMD_ALIGNED_TYPE_ON_MPL(T,ALIGN) BOOST_SIMD_ALIGNED_TYPE_ON(T,BOOST_SIMD_CONFIG_ALIGNMENT)
#endif

/*!
  @brief Macro wrapper for SIMD aligned type

  Wraps a type @c T so that it is aligned on current SIMD alignment constraint.

  @usage{preprocessor/aligned_type.cpp}

  @param T Type to align on current SIMD alignment
**/
#define BOOST_SIMD_ALIGNED_TYPE(T)                                             \
BOOST_SIMD_ALIGNED_TYPE_ON(T,BOOST_SIMD_CONFIG_ALIGNMENT)                      \
/**/

/*!
  @brief Macro wrapper for SIMD aligned type in template context

  Wraps a type @c T so that it is aligned on current SIMD alignment constraint.
  This macro is to be used when the type to mark as aligned is used in a template
  typedef.

  @par Rationale

  This variant is required as some older compiler don't accept alignment
  attribute applied on template parameters. In all other cases, it is equivalent
  to BOOST_SIMD_ALIGNED_TYPE.

  @param T Type to align on current SIMD alignment
**/
#define BOOST_SIMD_ALIGNED_TYPE_TPL(T)                                         \
BOOST_SIMD_ALIGNED_TYPE_ON_TPL(T,BOOST_SIMD_CONFIG_ALIGNMENT)                  \
/**/

#endif
