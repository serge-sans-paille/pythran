//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_NEW_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_NEW_ALLOCATOR_HPP_INCLUDED

#include <boost/simd/memory/details/new_allocator.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Allocator that uses the type's new operator for allocating memory

    @tparam Type of elements to allocate
  **/
  template<class T>
  struct new_allocator
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

      Standard internal meta-function to build an @c new_allocator<U> from an
      @c new_allocator<T>

      @tparam U Type to rebind the current new_allocator to
    **/
    template<class U>
    struct rebind
    {
      typedef new_allocator<U> other;
    };

    /// Default constructor
    new_allocator() {}

    /// Constructor from another SIMD new_allocator
    template<class U>
    new_allocator(new_allocator<U> const& ) {}

    /// Retrieve the address of an element
    pointer       address(reference r)       { return &r; }

    /// @overload
    const_pointer address(const_reference r) { return &r; }

    /// Maximum amount of memory that can be allocated
    size_type max_size() const  { return size_type(~0); }

    /// Performs the construction of a given value in a given memory block
    void construct(pointer p, const T& t)
    {
      p = new ((void*)p) value_type (t);
    }

    /// Performs the destruction of a given value in a given memory block
    void destroy(pointer p) { p->~value_type(); }

    /// Allocate a block of memory with T's new operator
    pointer allocate( size_type c, const void* = 0 ) const
    {
      return static_cast<T*>(details::new_allocate_impl<T>(c*sizeof(T), 0));
    }

    /// Deallocate a pointer allocated by the current new_allocator
    void deallocate (pointer p, size_type ) const
    {
      return details::new_deallocate_impl<T>(p, 0);
    }
  };

  /// Equality comparison between two new_allocators
  template<typename T>
  bool operator== (new_allocator<T> const&, new_allocator<T> const&)
  {
    return true;
  }

  /// Inequality comparison between two new_allocators
  template<typename T>
  bool operator!= (new_allocator<T> const&, new_allocator<T> const&)
  {
    return false;
  }

  /*!
    @brief Allocator that uses the type's new[] operator for allocating memory

    @tparam Type of elements to allocate
  **/
  template<class T>
  struct new_array_allocator
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

      Standard internal meta-function to build an @c new_array_allocator<U> from an
      @c new_array_allocator<T>

      @tparam U Type to rebind the current new_array_allocator to
    **/
    template<class U>
    struct rebind
    {
      typedef new_array_allocator<U> other;
    };

    /// Default constructor
    new_array_allocator() {}

    /// Constructor from another SIMD new_array_allocator
    template<class U>
    new_array_allocator(new_array_allocator<U> const& ) {}

    /// Retrieve the address of an element
    pointer       address(reference r)       { return &r; }

    /// @overload
    const_pointer address(const_reference r) { return &r; }

    /// Maximum amount of memory that can be allocated
    size_type max_size() const  { return size_type(~0); }

    /// Performs the construction of a given value in a given memory block
    void construct(pointer p, const T& t)
    {
      p = new ((void*)p) value_type (t);
    }

    /// Performs the destruction of a given value in a given memory block
    void destroy(pointer p) { p->~value_type(); }

    /// Allocate a block of memory with T's new operator
    pointer allocate( size_type c, const void* = 0 ) const
    {
      return static_cast<T*>(details::new_array_allocate_impl<T>(c*sizeof(T), 0));
    }

    /// Deallocate a pointer allocated by the current new_array_allocator
    void deallocate (pointer p, size_type ) const
    {
      return details::new_array_deallocate_impl<T>(p, 0);
    }
  };

  /// Equality comparison between two new_array_allocators
  template<typename T>
  bool operator== (new_array_allocator<T> const&, new_array_allocator<T> const&)
  {
    return true;
  }

  /// Inequality comparison between two new_array_allocators
  template<typename T>
  bool operator!= (new_array_allocator<T> const&, new_array_allocator<T> const&)
  {
    return false;
  }
} }

#endif
