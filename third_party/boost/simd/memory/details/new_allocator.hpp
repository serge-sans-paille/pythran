//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_NEW_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_NEW_ALLOCATOR_HPP_INCLUDED

namespace boost { namespace simd {namespace details
{
  template<void* (*F)(std::size_t)>
  struct new_dummy;

  template<void (*F)(void*)>
  struct delete_dummy;;

  template<class T>
  void* new_allocate_impl(std::size_t c, ...)
  {
    return ::operator new(c);
  }

  template<class T>
  void* new_allocate_impl(std::size_t c, new_dummy<&T::operator new>*)
  {
    return T::operator new(c);
  }

  template<class T>
  void new_deallocate_impl(void* p, ...)
  {
    ::operator delete(p);
  }

  template<class T>
  void new_deallocate_impl(void* p, delete_dummy<&T::operator delete>*)
  {
    T::operator delete(p);
  }

  template<class T>
  void* new_array_allocate_impl(std::size_t c, ...)
  {
    return ::operator new[](c);
  }

  template<class T>
  void* new_array_allocate_impl(std::size_t c, new_dummy<&T::operator new[]>*)
  {
    return T::operator new[](c);
  }

  template<class T>
  void new_array_deallocate_impl(void* p, ...)
  {
    ::operator delete[](p);
  }

  template<class T>
  void new_array_deallocate_impl(void* p, delete_dummy<&T::operator delete[]>*)
  {
    T::operator delete[](p);
  }
} } }

#endif
