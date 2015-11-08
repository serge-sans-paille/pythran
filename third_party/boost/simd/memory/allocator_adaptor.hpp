//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED

#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/forward/allocator.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  template<typename Allocator, std::size_t Alignment>
  struct allocator_adaptor : Allocator
  {
    typedef Allocator                             base_type;
    typedef typename base_type::value_type        value_type;
    typedef typename base_type::pointer           pointer;
    typedef typename base_type::const_pointer     const_pointer;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;
    typedef typename base_type::size_type         size_type;
    typedef typename base_type::difference_type   difference_type;

    /*!
      @brief Allocator type rebinding meta-function

      Standard internal meta-function to build an @c allocator<U> from an
      @c allocator<T>

      @tparam U Type to rebind the current allocator to
    **/
    template<typename U> struct rebind
    {
      typedef typename Allocator::template rebind<U>::other base;
      typedef allocator_adaptor<base,Alignment>             other;
    };

    /// Default constructor
    allocator_adaptor() : base_type() {}

    template<typename Z>
    allocator_adaptor ( allocator_adaptor<Z,Alignment> const& src)
                      : base_type(src.base())
    {}

    allocator_adaptor& operator=(allocator_adaptor const& src)
    {
      base_type::operator=(src);
      return *this;
    }

    /// Allocate a block of SIMD compatible memory
    pointer allocate( size_type c, const void* = 0 )
    {
      c *= sizeof(value_type);
      return reinterpret_cast<pointer>(simd::allocate<Alignment>( base(), c ));
    }

    /// Deallocate a pointer allocated by the current allocator
    void deallocate (pointer p, size_type )
    {
      boost::simd::deallocate(base(), p);
    }

    /// Return a reference to the adapted allocator
    base_type&        base()
    {
      return static_cast<base_type&>(*this);
    }

    /// @overload
    base_type const&  base() const
    {
      return static_cast<base_type const&>(*this);
    }
  };

  /// Equality comparison between two adapted allocators
  template<typename A, std::size_t N>
  bool operator== ( allocator_adaptor<A,N> const& a
                  , allocator_adaptor<A,N> const& b
                  )
  {
    return a.base() == b.base();
  }

  /// Inequality comparison between two adapted allocators
  template<typename A, std::size_t N>
  bool operator!= ( allocator_adaptor<A,N> const& a
                  , allocator_adaptor<A,N> const& b
                  )
  {
    return a.base() != b.base();
  }
} }

#endif
