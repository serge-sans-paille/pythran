//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_DEALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DEALLOCATE_HPP_INCLUDED

#include <boost/align/aligned_alloc.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api

    Deallocates space from a memory block of allocated by boost::simd::allocate.

    @tparam   T   Type of data to be released
    @param    ptr Pointer to release

    @return A pointer to the allocated space.
  */
  template<typename T> void deallocate(T* ptr)
  {
    return boost::alignment::aligned_free(ptr);
  }
} }

#endif
