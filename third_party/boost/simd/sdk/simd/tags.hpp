//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_TAGS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_TAGS_HPP_INCLUDED

namespace boost { namespace simd { namespace tag
{
  typedef boost::mpl::false_ not_simd_type;
  typedef boost::mpl::true_      simd_type;

} } }

#endif
