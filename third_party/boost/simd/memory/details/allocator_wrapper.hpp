//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T>
  inline T divceil(T a, T b)
  {
    return (a / b) + !!(a % b);
  }

  template<typename Allocator> struct allocator_malloc
  {
    allocator_malloc(Allocator& a) : alloc(a)
    {
    }

    void* operator()(std::size_t sz)
    {
      #ifndef BOOST_NO_EXCEPTIONS
      try
      {
        return alloc.allocate(details::divceil(sz, sizeof(typename Allocator::value_type)));
      }
      catch(...)
      {
        return 0;
      }
      #else
      return alloc.allocate(details::divceil(sz, sizeof(typename Allocator::value_type)));
      #endif
    }

    Allocator& alloc;

    private:
    allocator_malloc& operator=(allocator_malloc const&);
  };

  template<typename Allocator> struct allocator_free
  {
    allocator_free(Allocator& a) : alloc(a) {}

    void operator()(void* ptr, std::size_t sz)
    {
      typedef typename Allocator::pointer type;
      return alloc.deallocate(type(ptr), details::divceil(sz, sizeof(typename Allocator::value_type)));
    }

    Allocator& alloc;

    private:
    allocator_free& operator=(allocator_free const&);
  };
} } }

#endif
