//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_IS_ALIGNED_HPP_INCLUDED

#include <boost/align/is_aligned.hpp>

namespace boost { namespace simd { namespace detail
{
  inline bool is_aligned(const void* ptr,std::size_t alignment) BOOST_NOEXCEPT
  {
#if (BOOST_VERSION > 106000)
    return boost::alignment::is_aligned(ptr,alignment);
#else
    return boost::alignment::is_aligned(alignment,ptr);
#endif
  }

  inline bool is_aligned(std::size_t value,std::size_t alignment) BOOST_NOEXCEPT
  {
    return (value & (alignment - 1)) == 0;
  }
} } }

#endif
