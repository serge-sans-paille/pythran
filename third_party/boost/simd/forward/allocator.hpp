//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_FORWARD_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_FORWARD_ALLOCATOR_HPP_INCLUDED

#include <boost/simd/preprocessor/parameters.hpp>

#if !defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  template<typename T, std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct allocator;

  template<typename A, std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct allocator_adaptor;
} }

#endif

#endif
