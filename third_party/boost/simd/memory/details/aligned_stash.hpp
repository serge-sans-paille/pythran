//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_ALIGNED_STASH_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_ALIGNED_STASH_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace details
{
  struct aligned_block_header
  {
    std::size_t offset;
    std::size_t allocated_size;
  };
} } }

#endif
