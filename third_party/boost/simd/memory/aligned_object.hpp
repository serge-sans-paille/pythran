//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OBJECT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OBJECT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/align/aligned_alloc.hpp>

/*!
    @ingroup group-api

    This macros allow user-defined types to be dynamically allocated while respecting
    alignment constraints.

    @par Example:

    @code
    class custom_type
    {
      public:
      BOOST_SIMD_ALIGNED_OBJECT(custom_type);

      private:
      boost::simd::pack<char,16> q;
      boost::simd::pack<float> p;
    };
    @endcode

    @param Type Name of the type to adapt
**/
#define BOOST_SIMD_ALIGNED_OBJECT(Type)                                                             \
static void* operator new(std::size_t sz)                                                           \
{                                                                                                   \
  return boost::alignment::aligned_alloc(alignof(Type), sz);                                        \
}                                                                                                   \
                                                                                                    \
static void operator delete(void* ptr) BOOST_NOEXCEPT                                               \
{                                                                                                   \
  boost::alignment::aligned_free(ptr);                                                              \
}                                                                                                   \
                                                                                                    \
static void* operator new[](std::size_t sz)                                                         \
{                                                                                                   \
  return boost::alignment::aligned_alloc(alignof(Type), sz);                                        \
}                                                                                                   \
                                                                                                    \
static void operator delete[](void* ptr) BOOST_NOEXCEPT                                             \
{                                                                                                   \
  boost::alignment::aligned_free(ptr);                                                              \
}                                                                                                   \
/**/


#endif
