//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <boost/align/aligned_allocator.hpp>
#include <boost/align/aligned_delete.hpp>
#include <boost/simd/memory/preferred_alignment.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api

    Convenience alias defining a standard compliant allocator returning memory which alignment
    is compatible with the storage of boot::simd::pack<T,Cardinal> or the actual alignment of @c T
    if @c T is not an arithmetic type.

    @tparam T Type of data to be allocated
    @tparam Cardinal Cardinal of the pack to be used in the allocated memory.
                     By default, Cardinal is equal to the expected cardinal for a pack<T>.
  */
  template<typename T, std::size_t Cardinal = 0ULL>
  using allocator = boost::alignment::aligned_allocator<T,preferred_alignment<T,Cardinal>::value>;

  using aligned_delete = boost::alignment::aligned_delete;
} }

#endif
