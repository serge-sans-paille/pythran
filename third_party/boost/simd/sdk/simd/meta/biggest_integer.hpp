//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_BIGGEST_INTEGER_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_BIGGEST_INTEGER_HPP_INCLUDED

namespace boost { namespace simd { namespace meta
{
  template<class Extension>
  struct biggest_integer
  {
    typedef boost::simd::int64_t type;
  };

  template<class Extension>
  struct biggest_uinteger
  {
    typedef boost::simd::uint64_t type;
  };
} } }

#endif
