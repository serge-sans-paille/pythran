//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_STACK_BUFFER_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_STACK_BUFFER_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/preprocessor/align_on.hpp>
#include <boost/dispatch/attributes.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/assert.hpp>

#include <stdlib.h>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )     \
boost::iterator_range<type*> const                                             \
variableName( &__##variableName##helper_pointer__[ 0 ]                         \
            , &__##variableName##helper_pointer__[ size ]                      \
            )                                                                  \
/**/

/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_BUILTIN_ALLOCA( type, size )               \
::alloca( (size) * sizeof( type ) )                                            \
/**/

#if BOOST_SIMD_ALLOCA_ALIGNMENT >= BOOST_SIMD_CONFIG_ALIGNMENT
/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA                             \
BOOST_SIMD_STACK_BUFFER_AUX_BUILTIN_ALLOCA                                     \
/**/
#else
/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA( type, size )               \
reinterpret_cast<void *>                                                       \
(                                                                              \
  (                                                                            \
    reinterpret_cast</*std::*/intptr_t>                                        \
    (                                                                          \
      ::alloca( (size) * sizeof( type )                                        \
    + BOOST_SIMD_CONFIG_ALIGNMENT - BOOST_SIMD_ALLOCA_ALIGNMENT )              \
    )                                                                          \
    + BOOST_SIMD_CONFIG_ALIGNMENT - BOOST_SIMD_ALLOCA_ALIGNMENT                \
  ) & ~( BOOST_SIMD_CONFIG_ALIGNMENT - 1 )                                     \
)                                                                              \
/**/
#endif

/*!
  @brief Defines a memory buffer allocated on the stack

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper stack alignment.

  @usage{memory/stack_buffer.cpp}

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer
**/
#define BOOST_SIMD_STACK_BUFFER( variableName, type, size )                    \
type* BOOST_DISPATCH_RESTRICT const __##variableName##helper_pointer__  =      \
  static_cast<type * BOOST_DISPATCH_RESTRICT const>(                           \
    BOOST_SIMD_STACK_BUFFER_AUX_BUILTIN_ALLOCA( type, size )                   \
  );                                                                           \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/

/*!
  @brief Defines a memory buffer allocated on the stack suitable for SIMD

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment.

  @usage{memory/simd_stack_buffer.cpp}

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer
**/
#define BOOST_SIMD_ALIGNED_STACK_BUFFER( variableName, type, size )            \
BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT )                             \
type* BOOST_DISPATCH_RESTRICT const                                            \
__##variableName##helper_pointer__  =                                          \
  static_cast<type * BOOST_DISPATCH_RESTRICT const>(                           \
    BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA( type, size )                   \
  );                                                                           \
BOOST_ASSERT_MSG                                                               \
(                                                                              \
  reinterpret_cast<std::size_t>( __##variableName##helper_pointer__ )          \
  % (BOOST_SIMD_CONFIG_ALIGNMENT) == 0                                         \
,  "Alignment assumption breached in BOOST_SIMD_STACK_BUFFER"                  \
);                                                                             \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/

/*!
  @brief Defines a scoped memory buffer allocated on the stack

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment. This
  Range is made to be deallocated at current scope's exit.

  @usage{memory/scoped_buffer.cpp}

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer

**/
#ifndef __GNUC__
#define BOOST_SIMD_SCOPED_STACK_BUFFER( variableName, type, size )             \
BOOST_SIMD_STACK_BUFFER( variableName, type, size)                             \
/**/
#else
#define BOOST_SIMD_SCOPED_STACK_BUFFER( variableName, type, size )             \
type __##variableName##helper_pointer__[ size ];                               \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/
#endif


/*!
  @brief Defines a scoped memory buffer allocated on the stack suitable for SIMD

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment. This
  Range is made to be deallocated at current scope's exit.

  @usage{memory/simd_scoped_buffer.cpp}

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer

**/
#ifndef __GNUC__
#define BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER( variableName, type, size )     \
BOOST_SIMD_ALIGNED_STACK_BUFFER( variableName, type, size)                     \
/**/
#else
#define BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER( variableName, type, size )     \
BOOST_SIMD_ALIGN_ON( BOOST_SIMD_CONFIG_ALIGNMENT ) type                        \
__##variableName##helper_pointer__[ size ];                                    \
BOOST_ASSERT_MSG                                                               \
(                                                                              \
  reinterpret_cast<std::size_t>( __##variableName##helper_pointer__ )          \
  % (BOOST_SIMD_CONFIG_ALIGNMENT) == 0,                                        \
  "Alignment assumption breached in BOOST_SIMD_SCOPED_STACK_BUFFER"            \
);                                                                             \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/
#endif

#endif
