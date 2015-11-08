//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_REUSE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_REUSE_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/simd/memory/aligned_realloc.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/config.hpp>

#include <stdlib.h>

#if !defined(__APPLE__)
#include <malloc.h>
#else
#include <malloc/malloc.h>
#endif

namespace boost { namespace simd
{
  /*!
    @brief Low level aligned memory reuse

    Wraps system specific code for reusing an aligned memory block of
    @c size bytes with an address aligned on @c alignment.

    @par Semantic:

    For any given pointer @c ptr, integral @c size and @c alignment constraint,

    @code
    void* r = aligned_reuse(ptr,size,alignment);
    @endcode

    is equivalent to :

      - a aligned memory allocation is @c ptr is equal to 0;
      - a no-op if the requested @c size is equal to the old size of the memory
        block referenced by @c ptr;
      - a call to the system specific reallocation function followed by an
        alignment fix-up.

    Note that data is not preserved during reusing (contrary to aligned_realloc).

    @pre   @c alignment is a non-zero power of two.
    @param ptr        Pointer to reuse
    @param size       Number of bytes to allocate
    @param alignment  Alignment boundary to respect
    @param realloc_fn
    @return Pointer referencing the newly allocated memory block.
  **/
  template<typename ReallocFunction>
  inline void* aligned_reuse( void* ptr, std::size_t size, std::size_t alignment
                            , ReallocFunction realloc_fn
                            )
  {
    details::aligned_block_header* hdr = 0;
    if(ptr)
      hdr = static_cast<details::aligned_block_header*>(ptr) - 1;

    std::size_t nsz = size ? size + alignment + sizeof(details::aligned_block_header) : 0u;
    std::size_t old_offset = hdr ? hdr->offset : 0;

    void* fresh_ptr = realloc_fn( static_cast<char*>(ptr) - old_offset, nsz, hdr ? hdr->allocated_size : 0 );
    if(!fresh_ptr || !nsz)
      return fresh_ptr;

    std::size_t offset = simd::align_on(static_cast<char const*>(fresh_ptr)+sizeof(details::aligned_block_header), alignment) - static_cast<char const*>(fresh_ptr);

    hdr = reinterpret_cast<details::aligned_block_header*>(static_cast<char*>(fresh_ptr) + offset) - 1;
    hdr->offset = offset;
    hdr->allocated_size = size + alignment + sizeof(details::aligned_block_header) - offset;

    return static_cast<char*>(fresh_ptr) + offset;
  }

  /// @overload
  inline void* aligned_reuse(void* ptr, std::size_t size, std::size_t alignment)
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    std::size_t* const oldptr = static_cast<std::size_t*>(ptr)-1;

    if(ptr && !size)
    {
      ::_aligned_free(oldptr);
      return 0;
    }

    if(ptr && alignment == *oldptr)
    {
      std::size_t* fresh_ptr = static_cast<std::size_t*>(::_aligned_offset_realloc(oldptr, size+sizeof(std::size_t), alignment, sizeof(std::size_t)));
      if(!fresh_ptr)
        return 0;
      return fresh_ptr+1;
    }

    std::size_t* fresh_ptr = static_cast<std::size_t*>(::_aligned_offset_malloc(size+sizeof(std::size_t), alignment, sizeof(std::size_t)));
    if(!fresh_ptr)
      return 0;

    *fresh_ptr++ = alignment;

    if(ptr)
      ::_aligned_free(oldptr);

    return fresh_ptr;

    #elif (     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                                \
            ||  (defined( _GNU_SOURCE ) && defined(__linux) && !defined( __ANDROID__ ))            \
          )                                                                                        \
       && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    // Resizing to 0 free the pointer data and return
    if(size == 0)
    {
      ::free(ptr);
      return 0;
    }

    #ifdef __ANDROID__
    // https://groups.google.com/forum/?fromgroups=#!topic/android-ndk/VCEUpMfSh_o
    std::size_t const oldSize( ::dlmalloc_usable_size( ptr ) );
    #elif defined(__APPLE__)
    std::size_t const oldSize( ::malloc_size( ptr ) );
    #else
    std::size_t const oldSize( ::malloc_usable_size( ptr ) );
    #endif

    if( simd::is_aligned(ptr, alignment) )
    {
      if( ( oldSize - size ) < BOOST_SIMD_REALLOC_SHRINK_THRESHOLD )
      {
        return ptr;
      }
      else
      {
        // FIXME: realloc will free the old memory if it moves.
        // if it moves to a non-aligned memory segment and the subsequent
        // memory allocation fails, we break the invariant
        ptr = ::realloc(ptr, size);
        if( simd::is_aligned(ptr, alignment) )
          return ptr;
      }
    }

    void* const fresh_ptr = aligned_malloc(size, alignment);
    if(!fresh_ptr)
      return 0;

    ::free(ptr);

    return fresh_ptr;

    #else

    return aligned_reuse(ptr, size, alignment, custom_realloc_fn);

    #endif
  }
} }

#endif
