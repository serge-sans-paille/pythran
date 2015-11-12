//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SIZE_HPP_INCLUDED
#define NT2_SDK_META_SIZE_HPP_INCLUDED

#include <boost/simd/sdk/meta/size.hpp>

namespace nt2 { namespace meta
{
  using boost::simd::meta::has_same_size;
  using boost::simd::meta::has_different_size;
  using boost::simd::meta::has_smaller_size;
  using boost::simd::meta::has_larger_size;
  using boost::simd::meta::has_smaller_or_equal_size;
  using boost::simd::meta::has_larger_or_equal_size;
} }

#endif
