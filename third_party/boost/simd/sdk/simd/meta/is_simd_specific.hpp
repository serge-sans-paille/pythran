//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_SIMD_SPECIFIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_SIMD_SPECIFIC_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/forward/aligned_array.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T,class Extension>
  struct is_simd_specific : boost::mpl::false_ {};

  template<class T, std::size_t N, std::size_t Align>
  struct is_simd_specific < boost::simd::aligned_array<T, N, Align>
                          , tag::simd_emulation_< N * sizeof(T) >
                          > : boost::mpl::true_
  {};
} } }

#endif
