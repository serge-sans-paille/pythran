//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_FORWARD_SHIFTED_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_FORWARD_SHIFTED_ITERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/native_cardinal.hpp>

namespace boost { namespace simd
{
  template< typename Iterator
          , typename Region
          , std::size_t C = meta::native_cardinal<typename std::iterator_traits<Iterator>::value_type>::value
          >
  struct  shifted_iterator;
} }

#endif
