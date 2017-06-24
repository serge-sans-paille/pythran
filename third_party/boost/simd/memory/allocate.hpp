//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/align/aligned_alloc.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api

    Allocates space for a memory block of  @c size elements of type @c T
    with an alignment compatible with the current SIMD instructions set.

    @tparam   T Type of data to be allocated
    @param    size  Number of elements to allocate

    @return A pointer to the allocated space.
  */
  template<typename T> T* allocate(std::size_t size)
  {
    return reinterpret_cast<T*>(boost::alignment::aligned_alloc(pack<T>::alignment,size*sizeof(T)));
  }

  /*!
    @ingroup group-api

    Allocates space for a memory block of  @c size elements of type @c T
    with an alignment compatible with the selected SIMD instructions set @c arch.

    @tparam   T Type of data to be allocated
    @param    size  Number of elements to allocate
    @param    arch  Selected SIMD ISA mark-up

    @return  A pointer to the allocated space.
  */
  template<typename T, typename Arch> T* allocate(std::size_t size, Arch const& arch)
  {
    boost::ignore_unused(arch);
    return reinterpret_cast<T*>(boost::alignment::aligned_alloc(limits<Arch>::bytes,size*sizeof(T)));
  }
} }

#endif
