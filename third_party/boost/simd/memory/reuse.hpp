//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_REUSE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_REUSE_HPP_INCLUDED

#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/memory/aligned_reuse.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/meta/align_ptr.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Aligned memory reallocation

    reused a raw buffer of aligned bytes on an arbitrary alignment boundary
    without preserving contents.

    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate
    @param align   Hint on the alignment boundary used at allocation.

    @return A pointer to a reused memory block

    @pre @c align is a power of 2
    @post Returned pointer is aligned on @c align
  **/
  BOOST_FORCEINLINE void*
  reuse(void* ptr, std::size_t nbytes, std::size_t align)
  {
    return aligned_reuse(ptr,nbytes,align);
  }

  /*!
    @brief Aligned memory reallocation with a static alignment

    reused a raw buffer of aligned bytes on statically specified alignment
    boundary without preserving contents.

    @param ptr          Pointer to the memory to reuse.
    @param nbytes       New number of bytes to allocate
    @tparam Alignment   Hint on the alignment boundary used at allocation. By
                        default, this parameter is equal to the current system
                        SIMD alignment requirement.

    @return A pointer to a reused memory block

    @pre @c Alignment is a power of 2
    @post Returned pointer is aligned on @c Alignment
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE typename meta::align_ptr<void ,Alignment>::type
  reuse( void* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reuse(ptr, nbytes, Alignment));
  }

  /// INTERNAL ONLY
  BOOST_FORCEINLINE
  meta::align_ptr<void ,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  reuse( void* ptr, std::size_t nbytes )
  {
    return reuse<BOOST_SIMD_CONFIG_ALIGNMENT>( ptr, nbytes );
  }

  /*!
    @brief Aligned allocator-based memory reallocation

    reused a raw buffer of aligned bytes on an arbitrary alignment boundary
    using an allocator without preserving contents.

    @param alloc  Allocator performing the (de)allocation
    @param ptr    Pointer to the memory to reuse.
    @param nbytes New number of bytes to allocate
    @param align  Hint on the alignment boundary used at allocation. By default,
                  this parameter is equal to the current system SIMD alignment
                  requirement.

    @return A pointer to a reused memory block containing @c nbytes bytes.

    @pre @c align is a power of 2
    @post Returned pointer is aligned on @c align
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type<typename Allocator::pointer, void*>::type
  #endif
  reuse(Allocator& alloc, void* ptr, std::size_t nbytes, std::size_t align)
  {
// Resizing to 0 free the pointer data and return
    if(nbytes == 0)
    {
      deallocate(alloc, ptr);
      return 0;
    }

    // Reallocating empty pointer performs allocation
    if(ptr == 0)
      return allocate(alloc, nbytes, align);

    details::aligned_block_header* hdr = static_cast<details::aligned_block_header*>(ptr) - 1;
    std::size_t const oldSize( hdr->allocated_size );

    // Return if idempotent reallocation or small shrink is performed with good alignment
    if( ( oldSize - nbytes ) < BOOST_SIMD_REALLOC_SHRINK_THRESHOLD && is_aligned(ptr, align) )
    {
      return ptr;
    }

    // Else reallocate manually/copy/deallocate old data
    void* fresh_ptr = allocate(alloc, nbytes, align);
    if( !fresh_ptr )
      return 0;

    deallocate(alloc, ptr);

    return fresh_ptr;
  }

  /*!
    @brief Statically aligned allocator-based memory reallocation

    reused a raw buffer of aligned bytes on statically specified alignment
    boundary using an allocator without preserving contents. By default, this
    alignment is equal to current SIMD preferred alignment.

    @param alloc   Allocator performing the (de)allocation
    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate
    @tparam Alignment  Static Hint on the alignment boundary used at allocation.

    @return A pointer to a reused memory block containing @c nbytes bytes.

    @pre @c Alignment is a power of 2
    @post Returned pointer is aligned on @c Alignment
  **/
  template<std::size_t Alignment, class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , typename meta::align_ptr<void ,Alignment>::type
                          >::type
  #endif
  reuse( Allocator& alloc, void* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reuse(alloc,ptr,nbytes,Alignment));
  }

  /// @overload
  template<class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , typename meta::align_ptr<void>::type
                          >::type
  #endif
  reuse( Allocator& alloc, void* ptr, std::size_t nbytes )
  {
    return reuse<BOOST_SIMD_CONFIG_ALIGNMENT>(alloc,ptr,nbytes);
  }
} }

#endif
