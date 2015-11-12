//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/preprocessor/malloc.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

#include <algorithm>
#include <cstdlib>
#include <stdlib.h>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

namespace boost { namespace simd
{
#if defined(BOOST_SIMD_CUSTOM_MEMORY_HANDLERS)

  #if !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)
  #define BOOST_SIMD_MEMORY_NO_BUILTINS
  #endif

  BOOST_DISPATCH_NOTHROW BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_SIZE(1) void* custom_malloc_fn(std::size_t);
#else
  BOOST_DISPATCH_NOTHROW BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_SIZE(1)  inline
  void* custom_malloc_fn(std::size_t sz) { return std::malloc(sz); }
#endif

  /*!
    @brief Low level aligned memory allocation

    Wraps system specific code for allocating an aligned memory block of
    @c size bytes with an address aligned on @c alignment.

    @par Semantic:

    For any given integral @c size and @c alignment constraint,

    @code
    void* r = aligned_alloc(size,alignment);
    @endcode

    is equivalent to a call to the system specific allocation function followed
    by a potential alignment fix-up.

    @par Framework specific override

    By default, aligned_malloc use system specific functions to handle memory
    allocation. One can specify a custom allocation function to be used
    instead. This custom function must have a prototype equivalent to:

    @code
    void* f(std::size_t sz, std::size_t align);
    @endcode

    In this case, the following code:

    @code
    void* r = aligned_realloc(ptr,size,alignment, f);
    @endcode

    is equivalent to a call to @c f followed by an alignment fix-up.

    @pre   @c alignment is a non-zero power of two.

    @param size       Number of bytes to allocate
    @param alignment  Alignment boundary to respect
    @param malloc_fn  Function object to use for allocation of the base pointer

    @return Pointer referencing the newly allocated memory block.
  **/
  template<typename AllocFunction>
  BOOST_DISPATCH_NOTHROW BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_SIZE(1)
  inline void* aligned_malloc ( std::size_t size, std::size_t alignment
                              , AllocFunction malloc_fn
                              )
  {
    void* ptr = malloc_fn(size + alignment + sizeof(details::aligned_block_header));
    if(!ptr)
      return 0;

    std::size_t offset = simd::align_on(static_cast<char const*>(ptr)+sizeof(details::aligned_block_header), alignment) - static_cast<char const*>(ptr);

    details::aligned_block_header* hdr = reinterpret_cast<details::aligned_block_header*>(static_cast<char*>(ptr) + offset) - 1;
    hdr->offset = offset;
    hdr->allocated_size = size + alignment + sizeof(details::aligned_block_header) - offset;

    return static_cast<char*>(ptr) + offset;
  }

  /// @overload
  BOOST_DISPATCH_NOTHROW BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_SIZE(1)
  inline void* aligned_malloc(std::size_t size, std::size_t alignment)
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    // we need to store alignment for _aligned_realloc
    std::size_t* ptr = static_cast<std::size_t*>(::_aligned_offset_malloc(size+sizeof(std::size_t), alignment, sizeof(std::size_t)));
    if(!ptr)
      return 0;
    *ptr++ = alignment;
    return ptr;

    #elif     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )              \
          && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    alignment = std::max(alignment,sizeof(void*));

    void* result(0);

    BOOST_VERIFY(   (::posix_memalign(&result,alignment,size) == 0 )
                ||  ( result == 0 )
                );

    return result;

    #elif     defined( _GNU_SOURCE ) && defined(__linux) && !defined( __ANDROID__ ) \
          && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    /*
      Inexplicable yet consistently reproducible SIGSEGVs encountered on
      Android (4.1.3 emulator) with memalign (as if it actually allocates
      only a part of the requested memory).

      TODO:
      https://groups.google.com/a/chromium.org/forum/?fromgroups=#!msg/chromium-reviews/uil2eVbovQM/9slPSDkBvX8J
      http://codereview.chromium.org/10796020/diff/5018/base/memory/aligned_memory.h

                                       (25.10.2012.) (Domagoj Saric)
    */
    return ::memalign( alignment, size );

    #else

    return aligned_malloc( size, alignment, custom_malloc_fn );

    #endif
  }
} }

#endif
