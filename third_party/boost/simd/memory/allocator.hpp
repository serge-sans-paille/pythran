//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/forward/allocator.hpp>
#include <cstddef>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4100) // argument not reference in destroy()
#endif

namespace boost { namespace simd
{
  /*!
    @brief SIMD-aware allocator

    Provides a standard, stateless allocator that take allocates memory block
    compatible with current architecture SIMD constraints.

    @tparam Type of elements to allocate
  **/
  template<typename T, std::size_t Alignment> struct allocator
  {
    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    /*!
      @brief Allocator type rebinding meta-function

      Standard internal meta-function to build an @c allocator<U> from an
      @c allocator<T>

      @tparam U Type to rebind the current allocator to
    **/
    template<typename U> struct rebind
    {
      typedef allocator<U,Alignment> other;
    };

    /// Default constructor
    allocator() {}

    /// Constructor from another SIMD allocator
    template<typename U> allocator(allocator<U,Alignment> const& ) {}

    /// Constructor from another SIMD allocator
    template<typename U>
    allocator& operator=(allocator<U,Alignment> const& )
    {
      return *this;
    }

    /// Retrieve the address of an element
    pointer       address(reference r)       { return &r; }

    /// @overload
    const_pointer address(const_reference r) { return &r; }

    /// Maximum amount of memory that can be allocated
    size_type max_size() const  { return size_type(~0); }

    /// Performs the construction of a given value in a given memory block
    void construct(pointer p, const T& t)
    {
      p = new (p) value_type (t);
    }

    /// Performs the destruction of a given value in a given memory block
    void destroy(pointer p) { p->~value_type(); }

    /// Allocate a block of SIMD compatible memory
    pointer allocate( size_type c, const void* = 0 ) const
    {
      c *= sizeof(value_type);
      return reinterpret_cast<pointer>( boost::simd::allocate<Alignment>(c) );
    }

    /// Deallocate a pointer allocated by the current allocator
    void deallocate (pointer p, size_type ) const
    {
      boost::simd::deallocate( p );
    }
  };

  /// INTERNAL ONLY - Overload for void type
  template<std::size_t Alignment> struct allocator<void,Alignment>
  {
    typedef void*         pointer;
    typedef const void*   const_pointer;
    typedef void          value_type;

    template<typename U> struct rebind
    {
      typedef allocator<U,Alignment> other;
    };

    allocator() {}
    template<typename U> allocator(allocator<U,Alignment> const& ) {}
    template<typename U> allocator& operator=(allocator<U,Alignment> const& )
    {
      return *this;
    }
  };

  /// Equality comparison between two allocators
  template<typename T, std::size_t A>
  bool operator== (allocator<T,A> const&, allocator<T,A> const&)
  {
    return true;
  }

  /// Inequality comparison between two allocators
  template<typename T, std::size_t A>
  bool operator!= (allocator<T,A> const&, allocator<T,A> const&)
  {
    return false;
  }
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
