//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_FREE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_FREE_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/dispatch/attributes.hpp>

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

  void custom_free_fn(void*, std::size_t);
#else
  inline void custom_free_fn(void* ptr, std::size_t) { std::free(ptr); }
#endif

  /*!
    @brief Low level aligned memory deallocation

    Wraps system specific code for deallocating an aligned memory block.

    @par Semantic:

    For any given pointer @c ptr :

    @code
    void* r = aligned_free(ptr);
    @endcode

    is equivalent to :

      - a no-op if @c ptr is equal to 0;
      - a potential alignment fix-up followed by a system dependent memory
      deallocation.

    @par Framework specific override

    By default, aligned_realloc use system specific functions to handle memory
    reallocation. One can specify a custom reallocation function to be used
    instead. This custom function must have a prototype equivalent to:

    @code
    void f(void* ptr);
    @endcode

    In this case, the following code:

    @code
    void* r = aligned_free(ptr, f);
    @endcode

    is equivalent to an alignment fix-up followed by a call to @c f.

    @param ptr Pointer referencing the memory to deallocate
    @param free_fn Function object to use for deallocation of the base pointer
  **/
  template<typename FreeFunction>
  inline void aligned_free( void* ptr, FreeFunction free_fn)
  {
    if(!ptr)
      return;

    details::aligned_block_header* hdr = static_cast<details::aligned_block_header*>(ptr) - 1;
    std::size_t offset = hdr->offset;
    free_fn( static_cast<char*>(ptr) - offset, offset + hdr->allocated_size );
  }

  /// @overload
  inline void aligned_free( void* ptr )
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    if(!ptr)
      return;

    ::_aligned_free( static_cast<std::size_t*>(ptr)-1 );

    #elif (     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                                \
            ||  (defined( _GNU_SOURCE ) && defined(__linux) && !defined( __ANDROID__ ))            \
          )                                                                                        \
        && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    ::free( ptr );

    #else

    aligned_free(ptr, custom_free_fn);

    #endif
  }
} }

#endif
