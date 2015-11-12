//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_NEW_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_NEW_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/preprocessor/parameters.hpp>

/*!
  @brief Define alignment aware new and delete overload into a given POD type

  When used at class scope, BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE generates
  code for overloaded new and delete operator that use aligned allocation
  function over an arbitrary alignment boundary @c Alignment.

  @usage{preprocessor/overload_new_delete.cpp}

  @param Alignment Alignment boundary in bytes to use for dynamic allocation
         of current type.
**/
#define BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(Alignment)                       \
void* operator new(std::size_t sz, const std::nothrow_t& throw_status)         \
{                                                                              \
  return boost::simd::allocate<Alignment>(sz, throw_status);                   \
}                                                                              \
                                                                               \
void* operator new(std::size_t sz)                                             \
{                                                                              \
  return boost::simd::allocate<Alignment>(sz);                                 \
}                                                                              \
                                                                               \
void* operator new(std::size_t, void* p)                                       \
{                                                                              \
  return p;                                                                    \
}                                                                              \
                                                                               \
void* operator new[](std::size_t, void* p)                                     \
{                                                                              \
  return p;                                                                    \
}                                                                              \
                                                                               \
void* operator new[](std::size_t sz, const std::nothrow_t& throw_status)       \
{                                                                              \
  return boost::simd::allocate<Alignment>(sz, throw_status);                   \
}                                                                              \
                                                                               \
void* operator new[](std::size_t sz)                                           \
{                                                                              \
  return boost::simd::allocate<Alignment>(sz);                                 \
}                                                                              \
                                                                               \
void operator delete(void* m)                                                  \
{                                                                              \
  boost::simd::deallocate(m);                                                  \
}                                                                              \
                                                                               \
void operator delete[](void* m)                                                \
{                                                                              \
  boost::simd::deallocate(m);                                                  \
}                                                                              \
                                                                               \
void operator delete(void* m, const std::nothrow_t&)                           \
{                                                                              \
  boost::simd::deallocate(m);                                                  \
}                                                                              \
                                                                               \
void operator delete[](void* m, const std::nothrow_t&)                         \
{                                                                              \
  boost::simd::deallocate(m);                                                  \
}                                                                              \
void operator delete(void*, void*)                                             \
{                                                                              \
}                                                                              \
/**/

/*!
  @brief Define SIMD aware new and delete overload into a given POD type

  When used at class scope, BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE_SIMD generates
  code for overloaded new and delete operator that use aligned allocation
  function to satisfy current SIMD architecture alignment constraint.

  @usage{preprocessor/overload_new_delete_simd.cpp}
**/
#define BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE_SIMD()                           \
BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(BOOST_SIMD_CONFIG_ALIGNMENT)             \
/**/

#endif
