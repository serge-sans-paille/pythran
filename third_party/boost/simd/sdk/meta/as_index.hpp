//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_AS_INDEX_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_AS_INDEX_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct as_index
       : vector_of<std::size_t, meta::cardinal_of<T>::value>
  {
  };
} } }

#endif
