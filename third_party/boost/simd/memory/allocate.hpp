//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED

#include <boost/simd/meta/align_ptr.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/simd/memory/details/allocator_wrapper.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/preprocessor/malloc.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/throw_exception.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Allocation of aligned memory on custom alignment

    Allocate a buffer of bytes aligned on an arbitrary alignment.

    If used in non-throwing mode, it returns a null pointer when allocation
    fails. If used in throwing mode, it throws a std::bad_alloc instead.

    @param nbytes Number of bytes to allocate.
    @param align  Alignment boundary to follow

    @return A pointer to a memory block of @c nbytes bytes, aligned on @c align.
  **/
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_DISPATCH_NOTHROW BOOST_SIMD_ALLOC_SIZE(1)
  void* allocate( std::size_t nbytes, std::size_t align, std::nothrow_t const & )
  {
    return aligned_malloc(nbytes, align);
  }

  /// @overload
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_THROWS BOOST_SIMD_ALLOC_SIZE(1)
  void* allocate( std::size_t nbytes, std::size_t align )
  {
    void* result = allocate(nbytes, align, std::nothrow_t());
    if(!result) BOOST_THROW_EXCEPTION( std::bad_alloc() );

    return result;
  }

  /*!
    @brief Allocation of aligned memory with a static alignment

    Allocate a buffer of bytes aligned on an arbitrary statically specified
    alignment. By default, this static alignment is equal to the current SIMD
    alignment boundary.

    If used in non-throwing mode, it returns a null pointer when allocation
    fails. If used in throwing mode, it throws a std::bad_alloc instead.

    @tparam Alignment   Static alignment boundary to respect.

    @param nbytes     Number of bytes to allocate.
    @param t          Tag indicating the nothrow behavior of this function.

    @return A pointer to a memory block of @c nbytes bytes, aligned on @c align.
            For optimization purpose, this pointer is marked as properly aligned
            by using compiler specific attributes.
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE BOOST_DISPATCH_NOTHROW BOOST_SIMD_ALLOC_SIZE(1)
  typename meta::align_ptr<void,Alignment>::type
  allocate(std::size_t nbytes, std::nothrow_t const & t)
  {
    return align_ptr<Alignment>( allocate( nbytes, Alignment, t) );
  }

  /// @overload
  template<std::size_t Alignment>
  BOOST_FORCEINLINE BOOST_SIMD_ALLOC_THROWS BOOST_SIMD_ALLOC_SIZE(1)
  typename meta::align_ptr<void,Alignment>::type allocate(std::size_t nbytes)
  {
    return align_ptr<Alignment>( allocate( nbytes, Alignment) );
  }

  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_DISPATCH_NOTHROW BOOST_SIMD_ALLOC_SIZE(1)
  meta::align_ptr<void>::type
  allocate(std::size_t nbytes, std::nothrow_t const & t)
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>( nbytes, t );
  }

  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_SIMD_ALLOC_THROWS BOOST_SIMD_ALLOC_SIZE(1)
  meta::align_ptr<void>::type allocate( std::size_t nbytes )
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>(nbytes);
  }

  /*!
    @brief Allocator based allocation of aligned memory

    Allocate a buffer of bytes aligned on an arbitrary alignment using
    a custom allocator.

    @param alloc  The \c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.
    @param align  Alignment boundary to follow

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<class Allocator> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type<typename Allocator::pointer, void*>::type
  allocate( Allocator& alloc, std::size_t nbytes, std::size_t align )
  {
    return aligned_malloc ( nbytes, align
                          , details::allocator_malloc<Allocator>(alloc)
                          );
  }

  /*!
    @brief Allocator based allocation of aligned memory with static alignment

    Allocate a buffer of bytes aligned on an arbitrary statically specified
    alignment using a custom allocator.

    @param alloc  The @c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.

    @tparam Alignment  Alignment boundary to follow

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<std::size_t Alignment, class Allocator> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type< typename Allocator::pointer
                                , typename meta::align_ptr<void,Alignment>::type
                                >::type
  allocate( Allocator& alloc, std::size_t nbytes )
  {
    return align_ptr<Alignment>( allocate(alloc,nbytes,Alignment) );
  }

  /*!
    @brief Allocator based allocation of aligned memory

    Allocate a buffer of bytes aligned on current architecture preferred SIMD
    compatible alignment using a custom allocator.

    @param alloc  The \c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<class Allocator> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type< typename Allocator::pointer
                                , typename meta::align_ptr<void>::type
                                >::type
  allocate( Allocator& alloc, std::size_t nbytes )
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>(alloc,nbytes);
  }
} }

#endif
