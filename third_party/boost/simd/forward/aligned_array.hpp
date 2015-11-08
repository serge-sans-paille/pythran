//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_FORWARD_ALIGNED_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_FORWARD_ALIGNED_ARRAY_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/meta/prev_power_of_2.hpp>

#if !defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  template< class T
          , std::size_t N
          , std::size_t Align = (BOOST_SIMD_ARCH_ALIGNMENT > (N*sizeof(T)))
                              ? meta::prev_power_of_2_c< N*sizeof(T) >::value
                              : BOOST_SIMD_ARCH_ALIGNMENT
          >
  struct aligned_array;
} }

#endif

#endif
